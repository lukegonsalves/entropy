#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

// std::string reduce(std){

// }

// std::string applyEmbedding(){

// }
struct tokenPair{
    int first; 
    int second; 
    tokenPair(int a, int b): first(a), second(b) {}
    bool operator==(const tokenPair& rhs) const {
        return first == rhs.first && second == rhs.second;
    }
    bool operator<(const tokenPair& rhs) const {
    return std::tie(first, second) < std::tie(rhs.first, rhs.second);
}

};

template<>
struct std::hash<tokenPair>{
    std::size_t operator() (const tokenPair& v) const{
        return std::hash<int>()(v.first) ^ hash<int>()(v.second) << 1;
    }
};


void encode();

std::string decode(std::vector<int>& tokens, std::vector<std::pair<int, int>>& mergepairs, std::vector<int> mergetokens){
    // traverse the mergepairs -> mergetokens backwards.
    for(int i = mergetokens.size() - 1; i >= 0; i--){
        for(int j = 0; j < tokens.size(); j++)
        if( tokens[j] == mergetokens[i] ){
            tokens[j] = mergepairs[i].first;
            tokens.insert(tokens.begin() + j + 1, mergepairs[i].second);
        }
    }
    std::string out;
    for(int i = 0; i < tokens.size(); i++){
        out.append(1, (char) tokens[i]);
    }
    return out;
}

void merge(std::vector<int>& tokens, int a, int b, int idx, std::vector<int>& mergetokens, std::vector<std::pair<int, int>>& mergepairs){
    mergepairs.push_back({a, b});
    mergetokens.push_back(idx);

    for(int i = 0; i < tokens.size() - 1; i++ ){
        if ( tokens[i] == a && tokens[i+1] == b){
            tokens.erase(tokens.begin()+i);
            tokens[i] = idx;
        }
    }
};

void printSeq(const std::vector<int>& tokens){
    for(int i = 0; i < tokens.size(); i++){
        std::cout << tokens[i] <<" , ";
    }
    std::cout << std::endl;
}


int main(int argc, char**argv ){

    std::string input = "This is a piece of text used to demonstrate Huffman encoding. Shannon's first theorem, the source coding theorem says that the average bits per symbol B can encode a souurce of entropy H(z).";
    std::cout << "total chars: " << input.size() << std::endl;

    std::unordered_map<int, int> pairs;

    std::vector<int> tokens;
    for(int i = 0; i < input.size() - 1; i++){
        tokens.push_back( (int) input[i]); 
    }

    std::cout << "Pre-merge Token Seq: " << std::endl;
    printSeq(tokens);

    std::vector<int> mergetokens;
    std::vector<std::pair<int, int>> mergepairs;

    // Everything below here to be looped;
    int merge_count = 0;
    while( merge_count < 20 ){
        int max_token = *max_element(tokens.begin(), tokens.end());
        std::cout << "Max token in input seq: " << max_token << std::endl;
        // Count the pairs.
        std::unordered_map<tokenPair, int> freq;
        for(int i = 0; i < tokens.size() - 1; i++){
            freq[{tokens[i], tokens[i+1]}]++;
        }

        // To get the most freq; make a maxheap;
        std::priority_queue<std::pair<int, tokenPair>> q;
        for(auto ph : freq){
            // std::cout << "{" << ph.first.first << "," << ph.first.second <<  "} -> " << ph.second << ", ";
            q.push({ph.second, {ph.first.first, ph.first.second}});
        }
        
        // std::cout << "Stack output: " << std::endl;
        std::pair<int, int> curr;
        curr.first = q.top().second.first;
        curr.second = q.top().second.second;
        while( !q.empty() ){
            // std::cout << "{" << q.top().second.first << "," << q.top().second.second <<  "}: " << q.top().first << ", ";
            q.pop();
        }

        merge(tokens, curr.first, curr.second, max_token + 1, mergetokens, mergepairs);
        merge_count++;
    }



    std::cout << "Post-merge Token Seq: " << std::endl;
    printSeq(tokens);
    std::cout << "token seq length: " << tokens.size() << std::endl; 
    std::cout << "compression: " <<  (float)input.size() / tokens.size() << "x" << std::endl;
    // Print mapping {a, b} -> c 
    for(int i = 0; i < mergepairs.size(); i++){
        std::cout << "{" << mergepairs[i].first << "," << mergepairs[i].second <<  "} -> " << mergetokens[i] << std::endl;
    }

    std::cout << decode(tokens, mergepairs, mergetokens) << std::endl;
}

// Huffman encoding

