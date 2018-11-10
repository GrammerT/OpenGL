#ifndef QUATTREE_H
#define QUATTREE_H

#include <QObject>
#include <QRectF>
#include <QList>
#include <QQueue>
#include "supporttool.h"

#define SAFE_DELETE(ptr) if(ptr){delete ptr;ptr=NULL;}

template <class Value>
class QuatTree
{
    typedef QSharedPointer<Value> spValue;
    typedef QList<spValue> ValuesList;
    typedef QSharedPointer<QuatTree> spTree;
    typedef QVector<spTree> TreeList;
public:
    QuatTree(QRect &rect,int tree_deep=0)
        :_rect(rect)
    {
        QQueue<QuatTree*> queue;
        queue.push_back(this);
        for(auto level=1;tree_deep!=0;--tree_deep,level*=4)
        {
            for(auto i=0;i!=level;++i)
            {
                auto tree = queue.first();
                tree->Root();
                queue.pop_front();
                queue.push_back(tree->mPointer.LT);
                queue.push_back(tree->mPointer.RT);
                queue.push_back(tree->mPointer.LB);
                queue.push_back(tree->mPointer.RB);
                if(tree->isLeaf())
                {

                }
            }
        }
    }

    template <class Range>
    bool Insert(const spValue value,const Range &range)
    {
        auto tree = Contain(range);
        auto ret=NULL!=tree;
        if(ret)
        {
            tree->ValuesList.push_back(value);
        }
        return ret;
    }

    template <class Range>
    QuatTree<Value> *Contain(const Range &range)
    {
        QuatTree<Value> *ret = NULL;
        if(Contain(_rect,range))
        {
            if(!isLeaf())
            {
                if(ret==NULL) ret = mPointer.LT->Contain(range);
                if(ret==NULL) ret = mPointer.RT->Contain(range);
                if(ret==NULL) ret = mPointer.LB->Contain(range);
                if(ret==NULL) ret = mPointer.RB->Contain(range);
            }
            if(ret==NULL)
            {
                ret = this;
            }
        }
        return ret;
    }

    template <class Range>
    bool Remove(const Range &range)
    {
        auto tree = Contain(range);
        auto ret= NULL!=tree;
        if(ret)
        {
            tree->ValuesList.clear();
        }
        return ret;
    }

    QVector<QRect> leafs()
    {
        QVector<QRect> v;
        if(isLeaf())
        {
            v.push_back(this->_rect);
        }
        else
        {
            auto vLT = this->mPointer.LT->leafs();
            auto vRT = this->mPointer.RT->leafs();
            auto vLB = this->mPointer.LB->leafs();
            auto vRB = this->mPointer.RB->leafs();
            v.append(vLT);
            v.append(vRT);
            v.append(vLB);
            v.append(vRB);
        }
        return v;
    }

    spValue value() const
    {
        return _value;
    }
    void setValue(const spValue &value)
    {
        _value = value;
    }

private:
    void Root()
    {
        this->mPointer.LT = new QuatTree(QRect(_rect.topLeft(),_rect.center()));
        this->mPointer.RT = new QuatTree(QRect(_rect.left()+_rect.width()*0.5,_rect.top(),_rect.width()*0.5,_rect.height()*0.5));
        this->mPointer.LB = new QuatTree(QRect(_rect.left(),_rect.top()+_rect.height()*0.5,_rect.width()*0.5,_rect.height()*0.5));
        this->mPointer.RB = new QuatTree(QRect(_rect.center(),_rect.bottomRight()));
    }

    bool Remove(const spValue value)
    {
        return _values.removeOne(value);
    }

    inline bool isLeaf()
    {
        return   mPointer.LB==NULL
                &&mPointer.LT==NULL
                &&mPointer.RB==NULL
                &&mPointer.RT==NULL;
    }


private:
    struct Pointer
    {
        QuatTree *LT,*RT,*LB,*RB;
        Pointer()
            :LT(NULL)
            ,RT(NULL)
            ,LB(NULL)
            ,RB(NULL){}
        ~Pointer()
        {
            SAFE_DELETE(LT);
            SAFE_DELETE(RT);
            SAFE_DELETE(LB);
            SAFE_DELETE(RB);
        }
    };
    Pointer mPointer;
    QRect _rect;
    spValue _value;
};

#endif // QUATTREE_H
