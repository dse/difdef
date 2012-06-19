
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace Difdef {

struct PatienceNode {
    int value;
    PatienceNode *left;
    PatienceNode *down;
    PatienceNode(int v, PatienceNode *l, PatienceNode *d): value(v), left(l), down(d) { }
    ~PatienceNode() { delete down; }
};

static std::vector<int> patience_sequence(const std::vector<int> &v)
{
    std::vector<int> result;
    if (v.empty())
        return result;

    std::vector<PatienceNode *> top_cards;
    for (int i = 0; i < v.size(); ++i) {
        int val = v[i];
        /* Put "val" into the leftmost pile whose top card is greater than it. */
        bool handled = false;
        for (int j=0; j < top_cards.size(); ++j) {
            if (top_cards[j]->value > val) {
                PatienceNode *left = (j > 0) ? top_cards[j-1] : NULL;
                top_cards[j] = new PatienceNode(val, left, top_cards[j]);
                handled = true;
                break;
            }
        }
        if (!handled) {
            PatienceNode *left = top_cards.empty() ? NULL : top_cards[top_cards.size()-1];
            top_cards.push_back(new PatienceNode(val, left, NULL));
        }
    }

    /* Extract the longest common subsequence. */
    int n = top_cards.size();
    assert(n != 0);
    result.resize(n);
    PatienceNode *p = top_cards[top_cards.size()-1];
    for (int i=0; i < n; ++i) {
        assert(p != NULL);
        result[n-i-1] = p->value;
        p = p->left;
    }
    assert(p == NULL);

    assert(!result.empty());
    assert(result[0] <= result[result.size()-1]);
    return result;
}

std::vector<const std::string *> lcs_unique(const std::vector<const std::string *> &a,
                                      const std::vector<const std::string *> &b)
{
    size_t n = a.size();
    assert(b.size() == n);
    std::vector<int> indices(n);
    for (int i=0; i < n; ++i) {
        int index_of_ai_in_b = std::find(b.begin(), b.end(), a[i]) - b.begin();
        assert(0 <= index_of_ai_in_b && index_of_ai_in_b < n);
        indices[i] = index_of_ai_in_b;
    }
    std::vector<int> ps = patience_sequence(indices);
    std::vector<const std::string *> result;
    for (int i=0; i < ps.size(); ++i) {
        result.push_back(b[ps[i]]);
    }
    return result;
}

}