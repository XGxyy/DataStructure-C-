#pragma once

namespace G{
	template<class T>
	class TreeNode{
		T m_data;
		TreeNode<T>* m_left;
		TreeNode<T>* m_right;
	public:
		//构造函数,用初始化列表
		TreeNode(const T& val = T()) :
			m_data(val),
			m_left(nullptr),
			m_right(nullptr){}
	
		template<class T>
		friend class BinarySortTree;//模板类友元
	};
	
	template<class T>
	class BinarySortTree{
		TreeNode<T>* m_root;
		/*void destory(){
			if (m_root){
				TreeNode<T>* tmp = m_root;
				m_root = m_root->m_right;
				delete(m_root);
			}
		}*/
		void destory(TreeNode<T>* root){
			if (root){
				destroy(root->m_left);
				destory(root->m_right);
				delete root;
			}
	public:
		BinarySortTree() :
			m_root(nullptr){}
		
		bool insert(const T& val){
			if (m_root == nullptr){
				m_root = new TreeNode<T>(val);
				return true;
			}
	
			TreeNode<T>* cur = m_root;
			TreeNode<T>* pre = nullptr;
			//找pre
			while (cur){
				if (val < cur->m_data){
					pre = cur;
					cur = cur->m_left;
				}
				else if (val > cur->m_data){
					pre = cur;
					cur = cur->m_right;
				}
				else{
					return false;
				}
			}
			//赋值cur
			cur = new TreeNode<T>(val);
			if (val < pre->m_data){
				pre->m_left = cur;
			}
			else{
				pre->m_right = cur;
			}
			return true;
		}
	
		bool erase(const T& val){
	#if 0
			if (m_root == nullptr){
				m_root = new TreeNode<T>(val);
				return true;
			}
	
			TreeNode<T>* cur = m_root;
			TreeNode<T>* pre = nullptr;
			while (cur){
				if (val < cur->m_data){
					pre = cur;
					cur = cur->m_left;
				}
				else if (val > cur->m_data){
					pre = cur;
					cur = cur->m_right;
				}
				else{
					break;
				}
			}
			
			if (cur == nullptr){
			return false;
			}
	
			if (cur->m_left && cur->m_right){
	
			}
			else if (cur->m_left){
				if (cur->m_data < pre->m_data){
					pre->m_left = cur->m_left;
				}
				else{
					pre->m_right = cur->m_left;
				}
			}
			else{
				if (cur->m_data < pre->m_data){
					pre->m_left = cur->m_right;
				}
				else{
					pre->m_right = cur->m_right;
				}
				delete cur;
			}

			/*
			先看是不是有左右子树:
				①左右子树都有:
				a.左子树没有右孩子:
					直接让左孩子继承自己的右孩子和父亲
				b.左子树有右孩子:
					一路向右,找到最后一个右孩子,然后将这个孩子的左子树挂在
					它父亲的右子树上,然后让他继承要删除的节点的人际关系
				  当删除的节点是根节点,不用继承父亲关系,但是要修改根节点指向
				②只有左子树
				直接让左子树继承自己的父亲关系,如果要删除的是根,那么直接换根
				③其他
				直接让右子树或空继承自己的父亲关系,其他同上
			*/
	#else
			if (m_root == nullptr){
				return false;
			}
	
			TreeNode<T> * cur = m_root;
			TreeNode<T> * pre = nullptr;
	
			while (cur){
				if (val < cur->m_data){
					pre = cur;
					cur = cur->m_left;
				}
	
				else if (val > cur->m_data){
					pre = cur;
					cur = cur->m_right;
				}
	
				else{
					break;
				}
			}
	
			if (cur == nullptr){
				return false;
			}
			if (cur->m_left && cur->m_right){
				TreeNode<T> * cur2 = cur->m_left;
				TreeNode<T> * pre2 = cur;
				
				if (cur2->m_right){
					for (; cur2->m_right; pre2 = cur2, cur2 = cur2->m_right);
					pre2->m_right = cur2->m_left;
					cur2->m_left = cur->m_left;
				}
				cur2->m_right = cur->m_right;
				if (cur == pre){
	
				}
				if (cur->m_data < pre->m_data){
					pre->m_left = cur2;
				}
	
				else{
					pre->m_right = cur2;
				}
				delete cur;
			}
	
			else if (cur->m_left){
				if (cur == pre){
					m_root = cur->m_left;
				}
				else{
					if (cur->m_data < pre->m_data){
						pre->m_left = cur->m_left;
					}
	
					else{
						pre->m_right = cur->m_left;
					}
				}
				delete cur;
			}
	
			else{
				if (cur == pre){
					m_root = cur->m_left;
				}
				else{
					if (cur->m_data < pre->m_data){
						pre->m_left = cur->m_right;
					}
	
					else{
						pre->m_right = cur->m_right;
					}
				}
				delete cur;
			}
	#endif
		}
		~BinarySortTree(){
			destory();
		}
	};
}








