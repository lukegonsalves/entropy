#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <bits/stdc++.h>

// std::string reduce(std){

// }

// std::string applyEmbedding(){

// }

// merge, take the tokenised sequence {tokens}, replace any occurences of pair {a,b} with {idx};
std::vector<int> merge(std::vector<int> &tokens, int a, int b , int idx){
    std::vector<int> out;
    int i = 0;
    while( i < tokens.size() ){
        if( tokens[i] == a && tokens[i+1] == b && i < tokens.size() - 1 ){
            out.push_back(idx);
            i += 2;
        }
        else{
            out.push_back(tokens[i]);
            i++;
        }
    }
    return out;
}

void printSeq(const std::vector<int>& tokens){
    for(int i = 0; i < tokens.size(); i++){
        std::cout << tokens[i];
    }
    std::cout << std::endl;
}


int main(int argc, char**argv ){

    std::string input = "This is a piece of text used to demonstrate Huffman encoding";
    std::cout << "total chars: " << input.size() << std::endl;
    std::unordered_map<std::string, int> alphabet; // count the frequency of each 2 length string
    std::unordered_map<std::string, int> token; // assign a token value to each character

    for(int i = 0; i < input.size(); i++){
        alphabet[input.substr(i,2)]++;
        token[input.substr(i,1)] = i;
    }
    
    typedef std::pair<int, std::string> freq;

    std::priority_queue<freq> q;
    for(auto out : alphabet ){
        q.push({out.second, out.first});
    } 

    while(!q.empty()){ 
        std::cout << q.top().first << " | " << '{' << token[q.top().second.substr(0,1)] << ", "<< token[q.top().second.substr(1,1)] << "}" << std::endl;
        q.pop();
    }


    // Create tokenised seq
    std::cout << input << std::endl;
    std::vector<int> tokens;
    for(int i = 0; i < input.size(); i++){
        tokens.push_back(token[input.substr(i, 1)]);
        std::cout << tokens[i];
    }

    printSeq(tokens);
    // std::vector<int> randomList = {1, 2, 3, 4, 5};
    // randomList = merge(randomList, 4, 5, 99);
    // printSeq(randomList);
    
    // loop this, include manipulation of the hash maps.
    int max_p = *std::max_element() 
    int max_t = *std::max_element(tokens.begin(), tokens.end());
    tokens = merge(tokens, a, b, max_t + 1);

    // for(auto out : alphabet){
    //     std::cout << out.first << " | " << out.second << std::endl;
    // }


}

// Huffman encoding

