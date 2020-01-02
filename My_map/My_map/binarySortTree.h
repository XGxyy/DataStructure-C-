#pragma once

namespace G{
	template<class T>
	class TreeNode{
		T m_data;
		TreeNode<T>* m_left;
		TreeNode<T>* m_right;
	public:
		//���캯��,�ó�ʼ���б�
		TreeNode(const T& val = T()) :
			m_data(val),
			m_left(nullptr),
			m_right(nullptr){}
	
		template<class T>
		friend class BinarySortTree;//ģ������Ԫ
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
			//��pre
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
			//��ֵcur
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
			�ȿ��ǲ�������������:
				��������������:
				a.������û���Һ���:
					ֱ�������Ӽ̳��Լ����Һ��Ӻ͸���
				b.���������Һ���:
					һ·����,�ҵ����һ���Һ���,Ȼ��������ӵ�����������
					�����׵���������,Ȼ�������̳�Ҫɾ���Ľڵ���˼ʹ�ϵ
				  ��ɾ���Ľڵ��Ǹ��ڵ�,���ü̳и��׹�ϵ,����Ҫ�޸ĸ��ڵ�ָ��
				��ֻ��������
				ֱ�����������̳��Լ��ĸ��׹�ϵ,���Ҫɾ�����Ǹ�,��ôֱ�ӻ���
				������
				ֱ������������ռ̳��Լ��ĸ��׹�ϵ,����ͬ��
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








