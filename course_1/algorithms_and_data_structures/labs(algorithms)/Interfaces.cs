using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Algorithms.Trees {
    interface ITree {
        void Insert(int key);
        void Remove(int key);
        bool Search(int key);

        int[] InfixTraverse();
        int[] PrefixTraverse();
        int[] PostfixTraverse();
    }

    //  INFIX_TRAVERSE (inorder) — обойти всё дерево, следуя порядку (левое поддерево, вершина, правое поддерево). Элементы по возрастанию
    //  PREFIX_TRAVERSE (preorder) — обойти всё дерево, следуя порядку (вершина, левое поддерево, правое поддерево). Элементы, как в дереве
    //  POSTFIX_TRAVERSE (postorder) — обойти всё дерево, следуя порядку (левое поддерево, правое поддерево', вершина). Элементы в обратном порядке, как в дереве
}
namespace Algorithms.Heaps {

}
namespace Algorithms.Merges {

}
namespace Algorithms.HashTables {

}