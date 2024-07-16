#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Event {
    string name;
    string description;
    string venue;
};

class TrieNode {
public:
    map<char, TrieNode*> children;
    bool is_end_of_event;
    vector<Event> events;

    TrieNode() {
        is_end_of_event = false;
    }
};

class EventTrie {
private:
    TrieNode* root;

    void insertString(const string& str, const Event& event) {
        TrieNode* node = root;
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->events.push_back(event);
        }
        node->is_end_of_event = true;
    }

public:
    EventTrie() {
        root = new TrieNode();
    }

    void insert(const Event& event) {
        insertString(event.name, event);
        insertString(event.description, event);
        insertString(event.venue, event);
    }

    vector<Event> search(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return {};
            }
            node = node->children[c];
        }
        return node->events;
    }
};

int main() {
    vector<Event> events = {
        {"Music Festival", "A great music event", "Central Park"},
        {"Art Exhibition", "Exhibition of modern art", "Art Gallery"},
        {"Tech Conference", "Conference on new tech", "Convention Center"},
        {"Tech tec","tec","tec"}
    };

    EventTrie trie;

    // Insert events into the trie
    for (const auto& event : events) {
        trie.insert(event);
    }

    // Search for events by prefix
    auto result = trie.search("Music");
    cout << "Search results for 'Music':\n";
    for (const auto& event : result) {
        cout << "Name: " << event.name << ", Description: " << event.description << ", Venue: " << event.venue << endl;
    }

    result = trie.search("Tech");
    cout << "Search results for 'Tech':\n";
    for (const auto& event : result) {
        cout << "Name: " << event.name << ", Description: " << event.description << ", Venue: " << event.venue << endl;
    }

    result = trie.search("Convention");
    cout << "Search results for 'Convention':\n";
    for (const auto& event : result) {
        cout << "Name: " << event.name << ", Description: " << event.description << ", Venue: " << event.venue << endl;
    }

    return 0;
}
