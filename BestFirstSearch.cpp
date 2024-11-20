/* Create a graph as discussed in the Lab from following text.
1. Display the Adjacency Matrix of size 28 X 28.
2. Show the Output of Best First Search as discussed in the Lab  starting from Character 'e'.

 
"Everything was in confusion in the Oblonskys' house. The wife had
discovered that the husband was carrying on an intrigue with a French
girl, who had been a governess in their family, and she had announced to
her husband that she could not go on living in the same house with him.
This position of affairs had now lasted three days, and not only the
husband and wife themselves, but all the members of their family and
household, were painfully conscious of it. Every person in the house
felt that there was no sense in their living together, and that the
stray people brought together by chance in any inn had more in common
with one another than they, the members of the family and household of
the Oblonskys. The wife did not leave her own room, the husband had not
been at home for three days. The children ran wild all over the house;
the English governess quarreled with the housekeeper, and wrote to a
friend asking her to look out for a new situation for her; the man-cook
had walked off the day before just at dinner time; the kitchen-maid, and
the coachman had given warning.

Three days after the quarrel, Prince Stepan Arkadyevitch
Oblonsky--Stiva, as he was called in the fashionable world--woke up at
his usual hour, that is, at eight o'clock in the morning, not in his
wife's bedroom, but on the leather-covered sofa in his study. He turned
over his stout, well-cared-for person on the springy sofa, as though he
would sink into a long sleep again; he vigorously embraced the pillow on
the other side and buried his face in it; but all at once he jumped up,
sat up on the sofa, and opened his eyes.

Stepan Arkadyevitch's eyes twinkled gaily, and he pondered with a smile.
 There was a great deal more that was
delightful, only there's no putting it into words, or even expressing it
in one's thoughts awake." And noticing a gleam of light peeping in
beside one of the serge curtains, he cheerfully dropped his feet over
the edge of the sofa, and felt about with them for his slippers, a
present on his last birthday, worked for him by his wife on gold-colored
morocco. And, as he had done every day for the last nine years, he
stretched out his hand, without getting up, towards the place where his
dressing-gown always hung in his bedroom. And thereupon he suddenly
remembered that he was not sleeping in his wife's room, but in his
study, and why: the smile vanished from his face, he knitted his brows.

Most unpleasant of all was the first minute when, on coming, happy and
good-humored, from the theater, with a huge pear in his hand for his
wife, he had not found his wife in the drawing-room, to his surprise had
not found her in the study either, and saw her at last in her bedroom
with the unlucky letter that revealed everything in her hand.

She, his Dolly, forever fussing and worrying over household details, and
limited in her ideas, as he considered, was sitting perfectly still with
the letter in her hand, looking at him with an expression of horror,
despair, and indignation.

And at this recollection, Stepan Arkadyevitch, as is so often the case,
was not so much annoyed at the fact itself as at the way in which he had
met his wife's words.

There happened to him at that instant what does happen to people when
they are unexpectedly caught in something very disgraceful. He did not
succeed in adapting his face to the position in which he was placed
towards his wife by the discovery of his fault. Instead of being hurt,
denying, defending himself, begging forgiveness, instead of remaining
indifferent even--anything would have been better than what he did
do--his face utterly involuntarily (reflex spinal action, reflected
Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily
assumed its habitual, good-humored, and therefore idiotic smile.

This idiotic smile he could not forgive himself. Catching sight of that
smile, Dolly shuddered as though at physical pain, broke out with her
characteristic heat into a flood of cruel words, and rushed out of the
room. Since then she had refused to see her husband.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <cctype>
using namespace std;

const int SIZE = 28;
const char start = 'a';
const char end = 'z';
const char space = ' ';
const char period = '.';

vector<vector<int>> Build_Matrix(const string& text) {
    vector<vector<int>> graph(SIZE, vector<int>(SIZE, 0));
    unordered_map<char, int> Index;

    for (int i = 0; i < SIZE; ++i) {
        if (i < 26) {
            Index[start + i] = i;
        } else if (i == 26) {
            Index[space] = i;
        } else if (i == 27) {
            Index[period] = i;
        }
    }

    for (int i = 0; i < text.size() - 1; ++i) {
        char c1 = tolower(text[i]);
        char c2 = tolower(text[i + 1]);
        if (Index.find(c1) != Index.end() && Index.find(c2) != Index.end()) {
            graph[Index[c1]][Index[c2]]++;
        }
    }

    return graph;
}

void Display(const vector<vector<int>>& graph) {
    for (const auto& row : graph) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

struct Node {
    char character;
    int heur_value;  // Heuristic value based on indegree
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.heur_value > b.heur_value;  // Min-heap based on heuristic value (indegree)
    }
};

vector<char> BFS(const vector<vector<int>>& graph, char start_Char) {
    unordered_map<char, int> Index;
    vector<char> result;
    priority_queue<Node, vector<Node>, Compare> nodes;
    set<char> visited;

    // Mapping characters to indices
    for (int i = 0; i < SIZE; ++i) {
        if (i < 26) {
            Index[start + i] = i;
        } else if (i == 26) {
            Index[space] = i;
        } else if (i == 27) {
            Index[period] = i;
        }
    }

    // Check if start character is valid
    if (Index.find(start_Char) == Index.end()) {
        cerr << "Start character not found in the index." << endl;
        return result;
    }

    nodes.push({start_Char, 0});  // Start with the initial character

    while (!nodes.empty()) {
        Node current = nodes.top();
        nodes.pop();

        if (visited.find(current.character) != visited.end()) {
            continue;
        }
        visited.insert(current.character);
        result.push_back(current.character);

        int u = Index[current.character];

        // Calculate indegree for heuristic values
        int indegree = 0;
        for (int v = 0; v < SIZE; ++v) {
            indegree += graph[v][u];  // Count the incoming edges to 'u'
        }

        // Expand neighbors based on the indegree heuristic
        for (int v = 0; v < SIZE; ++v) {
            if (graph[u][v] >= 1) {  // If there's an outgoing edge from 'u' to 'v'
                char nextChar = (v < 26) ? start + v : (v == 26) ? space : period;

                if (visited.find(nextChar) == visited.end()) {
                    nodes.push({nextChar, indegree});
                }
            }
        }
    }
    return result;
}

int main() {
    string text = "Everything was in confusion in the Oblonskys' house.The wife had discovered that the husband was carrying on an intrigue with a French girl, who had been a governess in their family, and she had announced to her husband that she could not go on living in the same house with him. This position of affairs had now lasted three days, and not only the husband and wife themselves, but all the members of their family and household, were painfully conscious of it. Every person in the house felt that there was no sense in their living together, and that the stray people brought together by chance in any inn had more in common with one another than they, the members of the family and household of the Oblonskys. The wife did not leave her own room, the husband had not been at home for three days. The children ran wild all over the house; the English governess quarreled with the housekeeper, and wrote to a friend asking her to look out for a new situation for her; the man-cook had walked off the day before just at dinner time; the kitchen-maid, and the coachman had given warning. Three days after the quarrel, Prince Stepan Arkadyevitch Oblonsky--Stiva, as he was called in the fashionable world--woke up at his usual hour, that is, at eight o'clock in the morning, not in his wife's bedroom, but on the leather-covered sofa in his study. He turned over his stout, well-cared-for person on the springy sofa, as though he would sink into a long sleep again; he vigorously embraced the pillow on the other side and buried his face in it; but all at once he jumped up, sat up on the sofa, and opened his eyes. Stepan Arkadyevitch's eyes twinkled gaily, and he pondered with a smile. There was a great deal more that was delightful, only there's no putting it into words, or even expressing it in one's thoughts awake. And noticing a gleam of light peeping in beside one of the serge curtains, he cheerfully dropped his feet over the edge of the sofa, and felt about with them for his slippers, a present on his last birthday, worked for him by his wife on gold-colored morocco. And, as he had done every day for the last nine years, he stretched out his hand, without getting up, towards the place where his dressing-gown always hung in his bedroom. And thereupon he suddenly remembered that he was not sleeping in his wife's room, but in his study, and why: the smile vanished from his face, he knitted his brows. Most unpleasant of all was the first minute when, on coming, happy and good-humored, from the theater, with a huge pear in his hand for his wife, he had not found his wife in the drawing-room, to his surprise had not found her in the study either, and saw her at last in her bedroom with the unlucky letter that revealed everything in her hand. She, his Dolly, forever fussing and worrying over household details, and limited in her ideas, as he considered, was sitting perfectly still with the letter in her hand, looking at him with an expression of horror, despair, and indignation. And at this recollection, Stepan Arkadyevitch, as is so often the case, was not so much annoyed at the fact itself as at the way in which he had met his wife's words. There happened to him at that instant what does happen to people when they are unexpectedly caught in something very disgraceful. He did not succeed in adapting his face to the position in which he was placed towards his wife by the discovery of his fault. Instead of being hurt, denying, defending himself, begging forgiveness, instead of remaining indifferent even--anything would have been better than what he did do--his face utterly involuntarily (reflex spinal action, reflected Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily assumed its habitual, good-humored, and therefore idiotic smile. This idiotic smile he could not forgive himself. Catching sight of that smile, Dolly shuddered as though at physical pain, broke out with her characteristic heat into a flood of cruel words, and rushed out of the room. Since then she had refused to see her husband.";

    vector<vector<int>> graph = Build_Matrix(text);
    Display(graph);

    vector<char> traversal_result = BFS(graph, 'e');

    cout << "Traversal result: ";
    for (char c : traversal_result) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
