/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO
    if(!t->is_empty()){
        int left = compute_height<T>(t->left()) + 1;
        int right = compute_height<T>(t->right()) + 1;
        if(left >= right){
            height=left;
        }
        else{
            height=right;
        }
    }
    else{
        height=-1;
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!t->is_empty()){
        ret_val = compute_size<T>(t->left()) + compute_size<T>(t->right()) + 1;
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
     if(!tree->is_empty()){
        retVal = p(tree->item());
        retVal = retVal && prefix_process<T, Processor>(tree->left(), p);
        retVal = retVal && prefix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty())
    {
        retVal = infix_process<T, Processor>(tree->left(), p);
        retVal = retVal && p(tree->item());
        retVal = retVal && infix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty())
    {
        retVal = postfix_process<T, Processor>(tree->left(), p);
        retVal = retVal && postfix_process<T, Processor>(tree->right(), p);
        retVal = retVal && p(tree->item());
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    typename BTree<T>::Ref subtree;
    std::queue<typename BTree<T>::Ref> trees;
    trees.push(tree);

    while (!trees.empty() && go_on)
    {
        subtree = trees.front();
        if(!subtree->is_empty())
        {
            go_on = p(subtree->item());
            trees.push(subtree->left());
            trees.push(subtree->right());
        }
        trees.pop();
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p=[&out](T n) mutable->bool{
        out << n << " ";
        return true;
    };
    prefix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p=[&out](T n) mutable->bool{
        out << n << " ";
        return true;
    };
    infix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p=[&out](T n) mutable->bool{
        out << n << " ";
        return true;
    };
    postfix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p=[&out](T n) mutable->bool{
        out << n << " ";
        return true;
    };
    breadth_first_process<T>(tree,p);
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto f = [it, &found, &count](T n)mutable->bool {
        count++;
        if(it==n){
            found=true;
            return false;
        }
        return true;
    }; //recibe el nodo procesado e imprime por pantalla el nodo
    prefix_process<T>(tree, f);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T n)mutable->bool{
        count++;
        if(it==n){
            found=true;
            return false;
        }
        return true;
    };
    infix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T n)mutable->bool{
        count++;
        if(it==n){
            found=true;
            return false;
        }
        return true;
    };
    postfix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T n)mutable->bool{
        count++;
        if(it==n){
            found=true;
            return false;
        }
        return true;
    };
    breadth_first_process<T>(tree,p);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    if(!tree->is_empty()){
        if(!tree->right()->is_empty()){
            auto minRight = tree->right();
            while (!minRight->left()->is_empty()){
                minRight = minRight->left();
            }
            if(minRight->item()<= tree->item()){
                ret_val=false;
            }
        }
        if(!tree->left()->is_empty()){
            auto maxleft = tree->left();
            while (!maxleft->right()->is_empty()){
                maxleft = maxleft->right();
            }
            if(maxleft->item()>= tree->item()){
                ret_val=false;
            }
        }
        if(!check_btree_in_order<T>(tree->left()) || !check_btree_in_order<T>(tree->right())){
            ret_val = false;
        }
    }
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO
    if(!tree->is_empty())
    {
        if(v < tree->item()){
            ret_val=has_in_order(tree->left(), v);
        }
        else if(v > tree->item())
        {
            ret_val=has_in_order(tree->right(), v);
        }
        else if(v==tree->item())
        {
            ret_val=true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if(tree->is_empty())
    {
        tree->create_root(v);
    }
    else if (v < tree->item())
    {
        if(tree->left()->is_empty())
        {
            tree->set_left(BTree<T>::create(v));
        }
        else
        {
            insert_in_order(tree->left(),v);
        }
    }
    else if (v > tree->item())
    {
        if(tree->right()->is_empty())
        {
            tree->set_right(BTree<T>::create(v));
        }
        else
        {
            insert_in_order(tree->right(),v);
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
