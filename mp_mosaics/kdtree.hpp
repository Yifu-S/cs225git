/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

#include "kdtree.h"

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    else if ((first[curDim] == second[curDim]) && (first < second))  return true;

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sumPotential = 0.0;
    double sumCurrent = 0.0;
    for (int i = 0; i < Dim; i++)
    {
      sumPotential += (potential[i] - target[i]) * (potential[i] - target[i]);
      sumCurrent += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
    }

    if (sumPotential < sumCurrent)  return true;
    else if ((sumPotential == sumCurrent) && (potential < currentBest)) return true;

    return false;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTreeConstructorHelper(vector<Point<Dim>>& newVector, int left, int right, int dimension)
{
    if (left > right) return nullptr;
    vector<Point<Dim>> temp(newVector.begin()+left, newVector.begin()+right+1);
    int midIndex = (right + left) / 2;
    Point<Dim> minPoint = newVector[left];
    for (int j = left; j < right+1; j++)
    {
      minPoint = temp[j-left];
      int minIndex = j;
      for (int i = j; i < right+1; i++)
      {
        if ((minPoint[dimension] > temp[i-left][dimension]) || ((minPoint[dimension] == temp[i-left][dimension]) && (minPoint > temp[i-left])))  
        {
          minPoint = temp[i-left];
          minIndex = i;
        }
      }
      newVector[j] = minPoint;
      Point<Dim> pswap = temp[j-left];
      temp[j-left] = minPoint;
      temp[minIndex-left] = pswap;
    }
    KDTree<Dim>::KDTreeNode* curNode = new KDTree<Dim>::KDTreeNode();
    curNode->point = newVector[midIndex];
    curNode->left = KDTreeConstructorHelper(newVector, left, midIndex-1, (dimension+1) % Dim);
    curNode->right = KDTreeConstructorHelper(newVector, midIndex+1, right, (dimension+1) % Dim);
    return curNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> newVector(newPoints.begin(), newPoints.end());
    root = KDTreeConstructorHelper(newVector, 0, newVector.size()-1, 0);
    size = newVector.size();
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) 
  {
      clear();
      copy(rhs);
  }
  return *this;
}

template <int Dim>
void KDTree<Dim>::KDTreeDestructorHelper(KDTreeNode* curNode)
{
  if (curNode == nullptr) return;
  KDTreeDestructorHelper(curNode->left);
  KDTreeDestructorHelper(curNode->right);
  delete curNode;
  curNode = nullptr;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  size = 0;
  clear();
}

/* template <int Dim>
Point<Dim> KDTree<Dim>::findSmallestHyperrectangle(KDTree<Dim>::KDTreeNode*& curNode, const Point<Dim>& query, int dimension) const
{
  while (true)
  {
    if (curNode->left == nullptr && curNode->right == nullptr)  break;
    if (curNode->point[dimension] > query[dimension])
    {
      findSmallestHyperrectangle(curNode->left, query, (dimension+1) % Dim);
      break;
    }
    else if (curNode->point[dimension] == query[dimension] && query < curNode->point) 
    {
      findSmallestHyperrectangle(curNode->left, query, (dimension+1) % Dim);
      break;
    }
    else 
    {  
      findSmallestHyperrectangle(curNode->right, query, (dimension+1) % Dim);
      break;
    }
  }
  if (curNode->left == nullptr && curNode->right == nullptr)  return curNode;
  if (curNode->point[dimension] > query[dimension]) return findSmallestHyperrectangle(curNode->left, query, (dimension+1) % Dim);
  else if (curNode->point[dimension] == query[dimension] && query < curNode->point) 
    return findSmallestHyperrectangle(curNode->left, query, (dimension+1) % Dim);
  else 
    return findSmallestHyperrectangle(curNode->right, query, (dimension+1) % Dim);
  
} */

template <int Dim>
double KDTree<Dim>::pointDist(Point<Dim> p1, Point<Dim> p2) const
{
  double dist = 0.0;
  for (int i = 0; i < Dim; i++)
  {
    dist += ((p1[i] - p2[i]) * (p1[i] - p2[i]));
  }
  return dist;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(KDTreeNode* curNode, const Point<Dim>& query, int dimension, double& radius, KDTreeNode*& currentBest) const
{
  if (curNode == nullptr)  
  {
    radius = INFINITY;
    return Point<Dim>();
  }

  if (pointDist(query, curNode->point) == 0.0)
  {
    currentBest = curNode;
    radius = 0.0;
    return curNode->point;
  }
 
  if ((curNode->left == nullptr && curNode->right == nullptr) && 
    ((pointDist(query, curNode->point) < radius) || ((pointDist(query, curNode->point) == radius) && (curNode->point < currentBest->point))))
  {
    currentBest = curNode;
    radius = pointDist(query, curNode->point);
  }
  else
  {
    if ((query[dimension] < curNode->point[dimension]) || ((query[dimension] == curNode->point[dimension]) && (query < curNode->point))) 
    {
      if (curNode->left != nullptr)
      {
        findNearestNeighborHelper(curNode->left, query, (dimension+1) % Dim, radius, currentBest);
        if ((pointDist(query, curNode->point) < radius) || ((pointDist(query, curNode->point) == radius) && (curNode->point < currentBest->point)))
        {
          currentBest = curNode;
          radius = pointDist(query, curNode->point);
        }
        if ((curNode->right != nullptr) && ((curNode->point[dimension] - query[dimension]) * (curNode->point[dimension] - query[dimension]) <= radius))
        {
          findNearestNeighborHelper(curNode->right, query, (dimension+1) % Dim, radius, currentBest);          
        }
      }
      else if ((pointDist(query, curNode->point) < radius) || ((pointDist(query, curNode->point) == radius) && (curNode->point < currentBest->point)))
      {
        currentBest = curNode;
        radius = pointDist(query, currentBest->point);
      }
    }
    else  
    {
      if (curNode->right != nullptr)
      {
        findNearestNeighborHelper(curNode->right, query, (dimension+1) % Dim, radius, currentBest);
        if ((pointDist(query, curNode->point) < radius) || ((pointDist(query, curNode->point) == radius) && (curNode->point < currentBest->point)))
        {
          currentBest = curNode;
          radius = pointDist(query, curNode->point);
        }
        if ((curNode->left != nullptr) && ((curNode->point[dimension] - query[dimension]) * (curNode->point[dimension] - query[dimension]) <= radius))
        {
          findNearestNeighborHelper(curNode->left, query, (dimension+1) % Dim, radius, currentBest);          
        }
      }
      else if ((pointDist(query, curNode->point) < radius) || ((pointDist(query, curNode->point) == radius) && (curNode->point < currentBest->point)))
      {
        currentBest = curNode;
        radius = pointDist(query, currentBest->point);
      }
    }
  }
  return currentBest->point;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    KDTreeNode* currentBest = nullptr;
    double radius = INFINITY;
    return findNearestNeighborHelper(root, query, 0, radius, currentBest);
}

template <int Dim>
void KDTree<Dim>::clear()
{
  KDTreeDestructorHelper(root);
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other)
{
  size = other.size;
  root = nullptr;
  KDTreeCopyHelper(root, other.root);
}

template <int Dim>
void KDTree<Dim>::KDTreeCopyHelper(KDTreeNode*& curNode, KDTreeNode* otherNode)
{
  if (otherNode == nullptr) curNode = nullptr;
  else
  {
    curNode = new KDTree<Dim>::KDTreeNode();
    curNode->point = otherNode->point;
/*     curNode->left = nullptr;
    curNode->right = nullptr; */
    KDTreeCopyHelper(curNode->left, otherNode->left);
    KDTreeCopyHelper(curNode->right, otherNode->right);
  }
}