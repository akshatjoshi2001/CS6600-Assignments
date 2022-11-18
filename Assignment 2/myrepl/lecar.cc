#include <algorithm>
#include <iterator>
#include <math.h>
#include <random>

#include "cache.h"
#include "util.h"
#include <unordered_map>
using namespace std;



double w_lfu;
double w_lru;
double lambda = 0.45;
double d;
std::random_device rd;


unordered_map<uint32_t, vector<uint64_t>> frequency;
unordered_map<uint32_t, list<uint32_t>>  lru_list;
unordered_map<uint64_t,list<uint32_t>::iterator> lru_ptr_map;

unordered_map<uint32_t, list<uint32_t>> h_lfu;
unordered_map<uint32_t, list<uint32_t>> h_lru;

//uint64_t timestamp = 1;



void CACHE::initialize_replacement()
{
  
  w_lru = 1;
  w_lfu = 1;
  d = pow((double)0.005,1/((double)NUM_WAY));
  
}

// find replacement victim
uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{


  uint32_t lru_decision = *(lru_list[set].begin());
  uint32_t lfu_decision = max_element(frequency[set].begin(), frequency[set].end()) - frequency[set].begin();

  
  discrete_distribution<> d({w_lru, w_lfu});

  std::mt19937 gen(rd());

  uint32_t choice = d(gen);
 
  uint32_t to_be_evicted = (choice == 0) ? lru_decision : lfu_decision;
  auto begin = std::next(block.begin(), set * NUM_WAY);
  if (choice == 0)
  {
    if (h_lru[set].size() == 8 * NUM_WAY) {
      h_lru[set].pop_front();
    }
    uint64_t block_addr = ((std::next(begin, to_be_evicted))->address)>>(LOG2_BLOCK_SIZE);
    h_lru[set].push_back(block_addr);

    // Removing block from LRU data structures
    auto it = (lru_ptr_map.find(block_addr));
  
    lru_list[set].erase((*it).second);
    lru_ptr_map.erase(it);

  }
  else
  {
  
    if (h_lfu[set].size() == 8 * NUM_WAY) {
      h_lfu[set].pop_front();
    }
    uint64_t block_addr = ((std::next(begin, to_be_evicted))->address)>>(LOG2_BLOCK_SIZE);
    h_lfu[set].push_back(block_addr);

    // Removing block from LRU data structures
    auto it = (lru_ptr_map.find(block_addr));
  
    lru_list[set].erase((*it).second);
    lru_ptr_map.erase(it);
   
  }
  return to_be_evicted;
}

// called on every cache hit and cache fill
void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
 
 

   if(hit==0) {
    // on a miss update weights
    auto it1 = find(h_lru[set].begin(),h_lru[set].end(),((full_addr)>>LOG2_BLOCK_SIZE));
    auto it2 = find(h_lfu[set].begin(),h_lfu[set].end(),((full_addr)>>LOG2_BLOCK_SIZE));
    if(it1 != h_lru[set].end()) {
   
        uint32_t t = distance(it1,h_lru[set].end());
        double r = pow(d,t);
        w_lfu = w_lfu*exp(lambda*r);
        h_lru[set].erase(it1);
    }
    else if(it2 != h_lfu[set].end()) {
        uint32_t t = distance(it2, h_lfu[set].end());
        double r = pow(d,t);
        w_lru = w_lru*exp(lambda*r);
        h_lfu[set].erase(it2);

    }

    w_lru = w_lru/(w_lru+w_lfu);
    w_lfu = w_lfu/(w_lru+w_lfu);
  }


   auto begin = std::next(block.begin(), set * NUM_WAY);
  // Logic for LRU 
  auto it = lru_ptr_map.find((((full_addr)>>LOG2_BLOCK_SIZE)));
  if(it !=  lru_ptr_map.end()) {
    lru_list[set].erase((*it).second);
  }
  lru_list[set].push_back((way));
  lru_ptr_map[(((full_addr)>>LOG2_BLOCK_SIZE))] = (--lru_list[set].end());


  // Logic for LFU
  if (frequency[set].empty())
    frequency[set].resize(NUM_WAY);
  if (hit) {
    frequency[set][way]++;
  } else {
    frequency[set][way] = 1;
  }
}

void CACHE::replacement_final_stats() {}
