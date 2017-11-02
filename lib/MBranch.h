#ifndef MBRANCH_H
#define MBRANCH_H
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <iostream>

#include <string>
#include <vector>

using namespace std;


template <typename T1> class MBranch
{
	private:
		TTree* tree_;
		TBranch* branch_ = nullptr;
		//TLeaf* leaf_ = nullptr;
		string name_;
		vector<T1> data_;
		int error_ = 0;
	public:

		MBranch(const string& name) : name_(name)
	{
		//data_.resize(1);
	}

		~MBranch()
		{
		}

		void SetupRead(TTree* tree)
		{
			tree_ = tree;
			tree_->SetBranchAddress(name_.c_str(), data_.data());
			branch_ = tree_->GetBranch(name_.c_str());
			//leaf_ = branch_->FindLeaf(name_.c_str());
			//cout << "MAX " << name_ << " " << branch_->GetFillStyle() << endl; 
			if(branch_ != nullptr)
			{
				size_t maxsize = branch_->GetFillStyle();
				//cout << "MAX " << name_ << " " << maxsize << endl; 
				Resize(maxsize);
			}
			else
			{
				cerr << "BRANCH " << name_ << "not available" << endl;
				error_ = 1;
				data_.resize(1, 0);
			}
		}

		void SetupWrite(TTree* tree, const string& countbranch, const string& type)
		{
			tree_ = tree;
			if(countbranch.size() > 0)
			{
				branch_ = tree_->Branch(name_.c_str(), data_.data(), (name_+"["+countbranch+"]/"+type).c_str());
			}
			else
			{
				branch_ = tree_->Branch(name_.c_str(), data_.data(), (name_+"/"+type).c_str());
			}
			Resize(1);
		}

		void Load(bool load)
		{
			tree_->SetBranchStatus(name_.c_str(), load);	
		}

		//const T1& operator[](size_t i) const {return data_[i];}
		//T1& operator[](size_t i) { if(data_.size() <= i) {resize(i+1);} return data_[i];}
		T1& operator[](size_t i) {if(error_ > 0){return data_.at(0);} if(i >= data_.size()) {cout << i << " " << data_.size() << " " << name_ << endl;} return data_.at(i);}
		//const string& GetName() const {return name_;}
		//size_t GetSize() const {return size_;}
		void Resize(size_t size)
		{
			//cout << "Resize: " << name_ << " " << size << endl;
			if(size <= data_.size()){return;}
			data_.resize(size);
			branch_->SetAddress(data_.data());
			branch_->SetFillStyle(data_.size());
		}

};

#endif
