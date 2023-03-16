#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    class Iterator
    {
    public:
        // constructor for iterator
        Iterator() : isValid(false) {} // invalid iterator
        
        // constructor for a valid iterator
        Iterator(typename std::vector<ValueType>::iterator it, typename std::vector<ValueType>::const_iterator e) : itr(it), isValid(true), end(e) {}

        ValueType &get_value() const
        {
            // if itr is invalid then undefined behavior, no need to do a validity check
            return *itr; // dereference the value(vector) iterator
        }

        bool is_valid() const
        {
            return isValid;
        }

        void advance()
        {
            // iterator is invalid when this method is called (undefined behavior in spec) just return
            if (!isValid) return;
            
            ++itr; // advance the itr
            
            // if our iterator has reached the end after advancing then it becomes invalid
            if (itr == end) isValid = false;
            
        }

    private:
        bool isValid; // keeps track of whether or not the iterator is valid
        typename std::vector<ValueType>::iterator itr; // itr for the vector of values
        typename std::vector<ValueType>::const_iterator end; // keeps track of just past the last value in 'values'
    };

    TreeMultimap() : m_root(nullptr)
    {
        // when a tree is first initialized it has a root ptr of null
    }

    ~TreeMultimap()
    {
        m_root = clear(m_root); // root will be set to nullptr after this and whole tree is clear
    }

    void insert(const KeyType &key, const ValueType &value)
    {
        // if root is nullptr (our BST is empty) then we will insert the new key and value into the tree
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
        }
        
        Node* curr = m_root;
        for(;;)
        {
            if (key == curr->key) // if the current key equals target key
            {
                // we associate the value with the key by adding it to the vector
                curr->values.push_back(value);
                return;
            }
            if (key < curr->key) // the target key is less than the current key so we go to a left child (if exists)
            {
                if (curr->left != nullptr)
                    curr = curr->left;
                else
                {
                    curr->left = new Node(key, value);
                    return;
                }
            }
            else if (key > curr->key) // the target key is greater than the current key so we go to the right child (if exists)
            {
                if (curr->right != nullptr)
                    curr = curr->right;
                else
                {
                    curr->right = new Node(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType &key) const
    {
        Node* curr = this->m_root; // set curr to the root
        
        while (curr != nullptr) // iterate through the BST
        {
            if (key == curr->key)
                return Iterator(curr->values.begin(), curr->values.end());
            else if (key < curr->key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        
        return Iterator(); // returns an invalid iterator that doesn't refer to any value
    }

private:
    struct Node
    {
        // each node holds a key and a value (vector of values associated with a key)
        KeyType key;
        std::vector<ValueType> values;

        // each node can have a left or right child (BST)
        Node *left, *right;
        
        // constructor for a node (inserts a copy of the value passed in so don't pass by const ref)
        Node(const KeyType& i_key, ValueType i_value) : key(i_key), left(nullptr), right(nullptr)
        { values.push_back(i_value); }

    };
    
    Node* clear(Node* del) // clear the BST
    {
        if (del == nullptr)
            return nullptr;
        else
        {
            clear(del->left);
            clear(del->right);
            delete del;
        }
        
        return nullptr;
    }
    
    Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
