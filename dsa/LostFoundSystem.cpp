#include "LostFoundSystem.h"
//As clang does not have #include<bits/stdc++.h>
#include <iostream>
#include <string>
#include<queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cctype>

//item management 
void LostFoundSystem::addLostItem(Item item){
    if(item.name.empty() || item.color.empty() || item.category.empty() ||item.location.empty() || item.description.empty()){
        cout<<"Please fill all the Required details !"<<endl;
        return;
    }
    item.id=generateId();
    item.status="LOST";
    if(checkDuplicate(item,true)){
        cout<<"Item already reported lost"<<endl;
        return;
    }
    lostItems.push_back(item);
    lostItemMap[item.id] = item;
    cout<<"Lost Item Successfully Registered !"<<endl;
    cout<<"Item Id : "<<item.id<<endl;
    return;
}

void LostFoundSystem::addFoundItem(Item item){
    if(item.name.empty() || item.color.empty() || item.category.empty() ||item.location.empty() || item.description.empty()){
        cout<<"Please fill all the Required details !"<<endl;
        return;
    }
    item.id=generateId();
    item.status="FOUND";
    if(checkDuplicate(item,false)){
        cout<<"Item already reported lost"<<endl;
        return;
    }
    foundItems.push_back(item);
    foundItemMap[item.id] = item;
    cout<<"Founded Item Successfully Registered !"<<endl;
    cout<<"Item Id : "<<item.id<<endl;
    return;
}

void LostFoundSystem::displayLostItems(){
    if (lostItems.empty())
    {
        cout << "No lost items reported yet!"<<endl;
        return;
    }
    for(int i=0;i<lostItems.size();i++){
        cout<< i+1<<"."<<endl;
        cout<<"Item Name : "<<lostItems[i].name<<endl;
        cout<<"Item ID : "<<lostItems[i].id<<endl;
        cout<<"Item Category : "<<lostItems[i].category<<endl;
        cout<<"Item Color : "<<lostItems[i].color<<endl;
        cout<<"Item Location : "<<lostItems[i].location<<endl;
        cout<<"Item Date : "<<lostItems[i].date<<endl;
        cout<<"Item Description : "<<lostItems[i].description<<endl;
        cout<<"Item Status : "<<lostItems[i].status<<endl;
    }
}

void LostFoundSystem::displayFoundItems(){
    if (foundItems.empty())
    {
        cout << "No Founded items reported yet!"<<endl;
        return;
    }
    for(int i=0;i<foundItems.size();i++){
        cout<< i+1<<".\n";
        cout<<"Item Name : "<<foundItems[i].name<<endl;
        cout<<"Item ID : "<<foundItems[i].id<<endl;
        cout<<"Item Category : "<<foundItems[i].category<<endl;
        cout<<"Item Color : "<<foundItems[i].color<<endl;
        cout<<"Item Location : "<<foundItems[i].location<<endl;
        cout<<"Item Date : "<<foundItems[i].date<<endl;
        cout<<"Item Description : "<<foundItems[i].description<<endl;
        cout<<"Item Status : "<<foundItems[i].status<<endl;
        cout<<endl;
    }
}

// Delete lost item
bool LostFoundSystem::deleteLostItem(int id){
    if(lostItems.empty()){
        cout << "No Lost items reported yet!"<<endl;
        return false;
    }

    bool found = false;

    for(int i = 0; i < lostItems.size(); i++){
        if(lostItems[i].id == id){
            found = true;
            lostItems.erase(lostItems.begin() + i);
            lostItemMap.erase(id);
            cout << "Lost item deleted successfully!"<<endl;
            return true;
        }
    }

    if(!found){
        cout << "No Lost item with ID : " << id << " reported"<<endl;
        return false;
    }

    return false;
}

// Delete found item
bool LostFoundSystem::deleteFoundItem(int id){
    if(foundItems.empty()){
        cout << "No Found items reported yet!"<<endl;
        return false;
    }

    bool found = false;

    for(int i = 0; i < foundItems.size(); i++){
        if(foundItems[i].id == id){
            found = true;
            foundItems.erase(foundItems.begin() + i);
            foundItemMap.erase(id);
            cout << "Found item deleted successfully!"<<endl;
            return true;
        }
    }

    if(!found){
        cout << "No Found item with ID : " << id << " reported"<<endl;
        return false;
    }

    return false;
}


//searching

//Search by ID
Item* LostFoundSystem::searchById(int id)
{
    auto it = lostItemMap.find(id);
    if (it != lostItemMap.end())
    {
        return &(it->second);
    }
    auto it2 = foundItemMap.find(id);
    if (it2 != foundItemMap.end())
    {
        return &(it2->second);
    }
    cout << "Item not found!" << endl;
    return nullptr;
}

//Search by name
void LostFoundSystem::searchByName(string name){
  transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return tolower(c); });

  bool found = false;

  // Search in lost items
  for (Item& item : lostItems){
    string itemName = item.name;

    transform(itemName.begin(), itemName.end(), itemName.begin(), [](unsigned char c) { return tolower(c); });

    if (itemName.find(name) != string::npos){
      cout << "\nLost Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  // Search in found items
  for (Item& item : foundItems){
    string itemName = item.name;

    transform(itemName.begin(), itemName.end(), itemName.begin(), [](unsigned char c) { return tolower(c); });

    if (itemName.find(name) != string::npos){
      cout << "\nFound Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  if (!found){
    cout << "No item found with name: " << name << endl;
  }
}

//Search by category
void LostFoundSystem::searchByCategory(string category){
  // Convert search input to lowercase
  transform(category.begin(), category.end(), category.begin(), [](unsigned char c) { return tolower(c); });

  bool found = false;

  // Search in lost items
  for (Item& item : lostItems){
    string itemCategory = item.category;

    transform(itemCategory.begin(), itemCategory.end(), itemCategory.begin(), [](unsigned char c) { return tolower(c); });

    if (itemCategory.find(category) != string::npos){
      cout << "\nLost Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  // Search in found items
  for (Item& item : foundItems){
    string itemCategory = item.category;

    transform(itemCategory.begin(), itemCategory.end(), itemCategory.begin(), [](unsigned char c) { return tolower(c); });

    if (itemCategory.find(category) != string::npos){
      cout << "\nFound Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  if (!found){
      cout << "No item found in category: " << category << endl;
  }
}

//Search by location
void LostFoundSystem::searchByLocation(string location){
  // Convert search input to lowercase
  transform(location.begin(), location.end(), location.begin(), [](unsigned char c) { return tolower(c); });

  bool found = false;

  // Search in lost items
  for (Item& item : lostItems){
    string itemLocation = item.location;

    transform(itemLocation.begin(), itemLocation.end(), itemLocation.begin(), [](unsigned char c) { return tolower(c); });

    if (itemLocation.find(location) != string::npos){
      cout << "\nLost Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  // Search in found items
  for (Item& item : foundItems){
    string itemLocation = item.location;

    transform(itemLocation.begin(), itemLocation.end(), itemLocation.begin(), [](unsigned char c) { return tolower(c); });

    if (itemLocation.find(location) != string::npos){
      cout << "\nFound Item Found!"<<endl;
      cout << "ID: " << item.id << endl;
      cout << "Name: " << item.name << endl;
      cout << "Category: " << item.category << endl;
      cout << "Color: " << item.color << endl;
      cout << "Location: " << item.location << endl;
      cout << "Status: " << item.status << endl;

      found = true;
    }
  }

  if (!found){
      cout << "No item found at location: " << location << endl;
  }
}



//Matching functions
int LostFoundSystem :: compareName(const Item& lost, const Item& found){
    string n1=found.name;
    string n2=lost.name;
    transform(n1.begin(), n1.end(), n1.begin(),
            [](unsigned char c) {
                return tolower(c);
            });

    transform(n2.begin(), n2.end(), n2.begin(),
                [](unsigned char c) {
                    return tolower(c);
                });
    if(n1==n2) return 30;
    if(n1.find(n2)!=string::npos || n2.find(n1)!=string ::npos)
        return 15;
    return 0;
}

int LostFoundSystem::compareCategory(const Item& lost, const Item& found)
{
    string n1 = found.category;
    string n2 = lost.category;
    transform(n1.begin(), n1.end(), n1.begin(),
            [](unsigned char c) {
                return tolower(c);
            });

    transform(n2.begin(), n2.end(), n2.begin(),
                [](unsigned char c) {
                    return tolower(c);
                });
    if (n1 == n2)
        return 20;
    return 0;
}

int LostFoundSystem::compareColor(const Item& lost, const Item& found)
{
    string n1 = found.color;
    string n2 = lost.color;
    transform(n1.begin(), n1.end(), n1.begin(),
            [](unsigned char c) {
                return tolower(c);
            });

    transform(n2.begin(), n2.end(), n2.begin(),
                [](unsigned char c) {
                    return tolower(c);
                });
    if (n1 == n2)
        return 20;
    if (n1.find(n2) != string::npos ||
        n2.find(n1) != string::npos)
        return 10;
    return 0;
}

int LostFoundSystem::compareLocation(const Item& lost, const Item& found)
{
    string n1 = found.location;
    string n2 = lost.location;
    transform(n1.begin(), n1.end(), n1.begin(),
                [](unsigned char c) {
                    return tolower(c);
                });

    transform(n2.begin(), n2.end(), n2.begin(),
                [](unsigned char c) {
                    return tolower(c);
                });
    if (n1 == n2)
        return 20;
    if (n1.find(n2) != string::npos ||
        n2.find(n1) != string::npos)
        return 10;
    return 0;
    }

int LostFoundSystem::compareDate(const Item& lost, const Item& found)
{
    string n1 = found.date;
    string n2 = lost.date;
    if (n1 == n2)
        return 10;
    return 0;
}

int LostFoundSystem::calculateMatchScore(const Item& lost, const Item& found)
{
    int score = 0;

    score += compareName(lost, found);       // 30 points
    score += compareCategory(lost, found);   // 20 points
    score += compareColor(lost, found);      // 20 points
    score += compareLocation(lost, found);   // 20 points
    score += compareDate(lost, found);       // 10 points

    return score;
}

void LostFoundSystem::findMatches(int lostItemId){
    Item *lostItem=nullptr;
    for (Item& item : lostItems) {
        if (item.id == lostItemId) {
            lostItem = &item;
            break;
        }
    }
    if (lostItem == nullptr) {
        cout << "Lost item not found" << endl;
        return;
    }
    priority_queue<pair<int, Item>> pq;
    for (Item item : foundItems) {
        int score = calculateMatchScore(*lostItem, item);
        if (score >= 60) {
            pq.push({score, item});
        }
    }
    //display best matches
    while (!pq.empty()) {
        cout << "Match Score: " << pq.top().first << endl;
        cout << "Item Name: " << pq.top().second.name << endl;
        cout<<"Item ID: "<< pq.top().second.id << endl;
        pq.pop();
    }
    
}
//Claims

//Utility

// Generate unique ID
int LostFoundSystem::generateId(){
    static int id = 1;
    return id++;
}

// Check duplicate item
bool LostFoundSystem::checkDuplicate(Item& item, bool isLost)
{
    string key = item.name + "|" + item.category + "|" +
                    item.color + "|" + item.location;
    if (isLost)
    {
        if (lostItemMap.find(key) != lostItemMap.end())
            return true;
        lostItemMap.insert(key);
    }
    else
    {
        if (foundItemMap.find(key) != foundItemMap.end())
            return true;

        foundItemMap.insert(key);
    }
    return false;
}
