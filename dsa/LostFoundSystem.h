#ifndef LOSTFOUNDSYSTEM_H
#define LOSTFOUNDSYSTEM_H
#include "Item.h"
//As clang does not have #include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cctype>

using namespace std;
struct MatchResult {
    Item foundItem;
    int score;
};
class LostFoundSystem {

private:

    // Main storage
    vector<Item> lostItems;
    vector<Item> foundItems;

    // Fast ID lookup
    unordered_map<int, Item> lostItemMap;
    unordered_map<int, Item> foundItemMap;

    // Duplicate prevention
    unordered_set<string> itemKeys;

public:
    // 1. Item Management
    void addLostItem(Item item);
    void addFoundItem(Item item);

    void displayLostItems();
    void displayFoundItems();

    bool deleteLostItem(int id);
    bool deleteFoundItem(int id);

    // 2. Search
    Item* searchById(int id);
    void searchByName(string name);
    void searchByCategory(string category);
    void searchByLocation(string location);

    // 3. Matching
    int compareName(const Item& lost, const Item& found);
    int compareCategory(const Item& lost, const Item& found);
    int compareColor(const Item& lost, const Item& found);
    int compareLocation(const Item& lost, const Item& found);
    int compareDate(const Item& lost, const Item& found);

    int calculateMatchScore(const Item &lost, const Item& found);
    void findMatches(int lostItemId);
    void displayBestMatches(int lostItemId);

    // 4. Claims
    void createClaim(int lostItemId, int foundItemId, int claimantId);
    void displayClaims(int finderId);

    bool acceptClaim(int claimId, int finderId);
    bool rejectClaim(int claimId, int finderId);

    void markAsReturned(int foundItemId);

    // 5. Utility
    int generateId();
    bool checkDuplicate(Item& item,bool islostconst );
    void sortItems();
};

#endif
