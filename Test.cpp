#include <iostream>
#include <stdexcept>
#include <string>
#include "doctest.h"
#include <map>
#include <random>
#include <set>
#include <vector>
#include "BinaryTree.hpp"

using namespace ariel;

TEST_CASE("Tree check"){

    BinaryTree<char> treeCHAR;
   treeCHAR.add_root('A')
    .add_right('A','C').add_right('C','G').add_right('G','L').add_left('A','O').add_right('O','T');
    vector<char> checkChar({'T','O','L','G','C','A'});
    unsigned long indexChar=0;
    for (auto it1=treeCHAR.begin_postorder(); it1!=treeCHAR.end_postorder(); ++it1) {
        CHECK(*it1 == checkChar.at(indexChar++)) ;
    }  


    BinaryTree<int> treeINT;
    treeINT.add_root(10).add_left(10,100).add_left(100,200).add_left(200,300).add_left(300,400);
    vector<int> checkINT({400,300,200,100,10});

    string treeString;
    string vectorString;
    for(int run:checkINT){
        vectorString+=to_string(run);
    }
    for(int run:treeINT){
        treeString+=to_string(run);
    }
    
    CHECK(vectorString == treeString);

    BinaryTree<string> treeSTRING;
    treeSTRING.add_root("David").add_right("David","Ariel").add_left("David","H").add_left("H","C").add_right("H","++");
    vector<string> stringV({"C","H","++","David","Ariel"});
    unsigned long index=0;
    for(auto it=treeSTRING.begin_inorder() ; it!=treeSTRING.end_inorder();++it){
        CHECK(*it == stringV.at(index++));
    } 
    auto it=treeSTRING.begin_inorder();
    CHECK(*it == "C"); ++it;
    CHECK(*it == "H"); ++it;
    CHECK(*it == "++"); ++it;
    CHECK(*it == "David"); ++it;
    CHECK(*it == "Ariel"); ++it;
    ++it;
    CHECK(it == treeSTRING.end_inorder());

    BinaryTree<double> treeDOUBLE;
    treeDOUBLE.add_root(0.1).add_right(0.1,0.7).add_right(0.7,0.23).add_left(0.1,0.2).add_left(0.2,0.5).add_right(0.2,0.9)
    .add_right(0.7,0.23).add_left(0.7,0.11);
    auto itDouble=treeDOUBLE.begin_preorder();
    CHECK(*itDouble == 0.1); ++itDouble;
    CHECK(*itDouble == 0.2); ++itDouble;
    CHECK(*itDouble == 0.5); ++itDouble;
    CHECK(*itDouble == 0.9); ++itDouble;
    CHECK(*itDouble == 0.7); ++itDouble;
    CHECK(*itDouble == 0.11); ++itDouble;
    CHECK(*itDouble == 0.23); ++itDouble;
    CHECK(itDouble == treeDOUBLE.end_preorder()); 



}
