#include<iostream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;
//这里每个班有10个人 ,十个班 
const int MAX = 20;
const int kechengnum = 10;
const int MAXB = 11;

int B[kechengnum]; //课程 
const int FenDuan = 5; //成绩分为五个段
 
vector<int> richeng[kechengnum];
int changci = 0;
int nowsy = 10;
bool flag1[kechengnum] = {0};  //记录科目考试结束 
vector<int> jishu[kechengnum]; //记录班级考试信息，以课程为单位 
bool chongtu[kechengnum][kechengnum] = {0};//记录冲突  单独考一门课程的时候与其他课程的冲突 

class jistudent
{
protected:
	string name;
	int xuehao;
	int banji;
	int b[kechengnum];
	int kecheng1;
	int kecheng2;
	int kecheng3;
	int sum;
	int sum1;
public:
	virtual void showsum()  const  
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的总成绩: " << (b[kecheng1] + b[kecheng2] + b[kecheng3]) << endl;
	}
	virtual void showkecheng(int k) const 
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的课程" << k << "成绩: " << b[k] << endl;
	}
	virtual void returnsum() 
	{
		sum = (b[kecheng1] + b[kecheng2] + b[kecheng3])/3;
	}
	virtual void returnsum1()
	{
		sum1 = (b[kecheng1] + b[kecheng2] + b[kecheng3]);
	}
	virtual void showsuoyou() const 
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的课程" << kecheng1 << "成绩: "  << b[kecheng1] << " 学生的课程" << kecheng2 << "成绩: "  << b[kecheng2] << " 学生的课程" << kecheng3 << "成绩: "  << b[kecheng3] << " 学生的总成绩: " << (b[kecheng1] + b[kecheng2] + b[kecheng3]) << endl;
	}
};

class Class;
class grade;

class student : jistudent
{
public:
	friend class Class;
	friend class grade;
	void showkecheng1()  const
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的课程" << kecheng1 << "成绩: " << b[kecheng1] << endl;
	}
	void showkecheng2()  const 
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的课程" << kecheng2 << "成绩: " << b[kecheng2] << endl;
	}	
	void showkecheng3()  const 
	{
		cout << "学生的学号: " << xuehao << " 学生的班级: " << banji << " 学生的名字: " << name << " 学生的课程" << kecheng3 << "成绩: " << b[kecheng3] << endl;
	}
	student & operator=(const student& sd)
	{
		name = sd.name;
		xuehao = sd.xuehao;
		kecheng1 = sd.kecheng1;
		kecheng2 = sd.kecheng2;
		kecheng3 = sd.kecheng3;
		for (int i= 0;i<kechengnum;i++)
		{
			b[i] = sd.b[i];
		}
		sum = sd.sum;
		sum1 = sd.sum1;
		banji = sd.banji;
		return *this;
	}
};


class Class 
{
private:
	student sd[MAX]; //按总成绩排名; 
	student sd1[MAX]; //按课程1排名;
	student sd2[MAX]; //按课程2排名;
	student sd3[MAX]; //按课程3排名; 
	vector<student> fenduansum[FenDuan];//存人这个存在 各分段 
	vector<student> fenduankecheng1[FenDuan];
	vector<student> fenduankecheng2[FenDuan];
	vector<student> fenduankecheng3[FenDuan];
	int fenduansumnum[FenDuan] = {0};        //存各分段人数 
	int fenduankecheng1num[FenDuan] = {0};
	int fenduankecheng2num[FenDuan] = {0};
	int fenduankecheng3num[FenDuan] = {0};
	int kecheng1;  
	int kecheng2;
	int kecheng3;
public:
	friend class grade; //友元类 
	void showsum() const ;
	void showsuoyou() const ;
	void showkecheng1()  const; //输出以各种排名的学生的位次和信息 
	void showkecheng2() const ;
	void showkecheng3() const ;
	void showsumfenduan() const ;      //按分段进行输出学生的信息; 
	void showkecheng1fenduan() const ;
	void showkecheng2fenduan() const ;
	void showkecheng3fenduan() const ; 
	void paixusum(int left = 0,int right = MAX-1);        //排序算法,这里使用快排 
	void paixukecheng1(int left = 0,int right = MAX-1);
	void paixukecheng2(int left = 0,int right = MAX-1);
	void paixukecheng3(int left = 0,int right = MAX-1);
	void tongjisuoyou();//在排位之后进行统计  包括存人和人数 各个成绩排名的都存 
	void chazhaosum(string fenshuduan) const ;      //查找班级个体的各个分数段的人数和其所有学生信息 
	void chazhaokecheng1(string fenshuduan) const ;
	void chazhaokecheng2(string fenshuduan) const ;
	void chazhaokecheng3(string fenshuduan) const ;
};

class grade  //一个年级 
{
private:
	Class c[MAXB];    //十个普通班级班级 
	student sd[MAX*10];//按总成绩排名 
	int fenduankechengnum[kechengnum][FenDuan] = {0};  
	vector<student> fenduankecheng[kechengnum][FenDuan];
	vector<student> fenduansum[FenDuan];//存人这个存在 各分段 
	int fenduansumnum[FenDuan] = {0};           //存各分段人数 
public:
	virtual void showzhidingbanjifenduan(int i,int kecheng) const ; //指定班级分段输出 
	virtual void paixusum(int left = 0,int right = MAX*10-1);        //排序算法,这里使用快排 
	virtual void tongjisuoyou();//在排位之后进行统计  包括存人和人数 各个成绩排名的都存 
	void showsum() const ; // 按总成绩直接输出名次
	void showfenbanji() const ;//按班级输出名次 
	void showzhidingbanji(int i) const ;//指定班级进行输出学生信息 
	void showsumfenduan() const ;      //按分段进行输出学生的信息; 
	void showkechengfenduan(int k) const ;
	virtual void chazhaosum(string fenshuduan) const ;      //查找班级个体的各个分数段的人数和其所有学生信息 
	virtual void chazhaokecheng(string fenshuduan,int k) const;
	void chazhaojutistudent(int xuehao) const;  //根据学号查找学生的信息 
	virtual void paixusuoyoubanji(); //排序所有班级 
	void paixukechengfenduan(int a ,int b,int left,int right);
	void paixusuoyoukechengfenduan();
	
	void richengtanxin();
	virtual void ceshixinxi() ;
};
 


bool panduankaowan()
{
	for (int i = 0;i<kechengnum;i++)
	{
		if (!flag1[i])
			return false;
	}
	return true;
} 

void  digui(vector<int> buchongtu,vector<int> &jieguo,int sy)
{
	if (buchongtu.size()==0)
	{
		if (nowsy<=sy)
			return ;
		else
		{
			nowsy = sy;
			richeng[changci] = jieguo;
			return ;
		}
	}
	for (int g= 0;g<int(buchongtu.size());g++)
	{
		vector<int> buchongtu1;
		jieguo.push_back(buchongtu[g]);
		int xiayige = buchongtu[g];
		sy -= jishu[buchongtu[g]].size();
		for (int i = 0;i<int(buchongtu.size());i++)
		{
			if (!(flag1[buchongtu[i]])&&!(chongtu[xiayige][buchongtu[i]]))
				buchongtu1.push_back(buchongtu[i]);
		}
		digui(buchongtu1,jieguo,sy);
		jieguo.erase(jieguo.end()-1,jieguo.end()); 
	}
}

void grade::richengtanxin() //日程贪心 
{
	for (int i = 1;i<MAXB;i++)
	{
		jishu[c[i].kecheng1].push_back(i);
		jishu[c[i].kecheng2].push_back(i);
		jishu[c[i].kecheng3].push_back(i);
	}
	
	for (int i = 0;i<kechengnum;i++)
	{
		bool flagbx[MAXB] = {0};
		for (int o = 0;o<int(jishu[i].size());o++)
		{
			flagbx[jishu[i][o]] = true;
		}
		
		int sy = 10 - jishu[i].size();
		for (int j = 0;j<kechengnum;j++)
		{
			if (i==j)
			{
				chongtu[i][j] = true;
				if (i==3)
				continue;
			}
			if (sy<int(jishu[j].size()))
			{
				chongtu[i][j] = true;
				continue;
			}
			else
			{
				for (int z = 0;z<int(jishu[j].size());z++)
				{
					if (flagbx[jishu[j][z]])
					{
						chongtu[i][j] = true;
						continue;
					}
				}
			}
		}
	}

	while (!panduankaowan())
	{
		for (int a = 0;a < kechengnum;a++)
		{
			if (flag1[a])
			{
				continue;
			}
			vector<int> jieguo;//记录每次的结果 
			jieguo.push_back(a);
			vector<int> buchongtu;
			int sy = 10 - jishu[a].size();
			for (int b = 0;b<kechengnum;b++)  
			{
				if (!flag1[b]&&!chongtu[a][b])
					buchongtu.push_back(b);
			}
			digui(buchongtu,jieguo,sy);
		}
		for (int i = 0;i<int(richeng[changci].size());i++)
		{
			flag1[richeng[changci][i]] = true;
		}
		changci++;
		nowsy=10;
	}
	
	for (int i = 0;i<changci;i++)
	{
		cout << "第" << i+1 << "场次考: " << endl;
		for (int j = 0;j<int(richeng[i].size());j++)
		{
			cout << "课程: " << richeng[i][j] << "考试班级为: ";
			for (int a = 0;a<int(jishu[richeng[i][j]].size());a++)
			{
				cout << "B" << jishu[richeng[i][j]][a] << " "; 
			}
			cout << endl;
		}
		cout << endl;
	}
}


void Class::showsum() const 
{
	for (int i = 0;i<MAX;i++)
		sd[i].showsum();
}

void Class::showkecheng1() const 
{
	for (int i = 0;i<MAX;i++)
		sd1[i].showkecheng1(); 
}

void Class::showkecheng2() const 
{
	for (int i= 0;i<MAX;i++)
		sd2[i].showkecheng2();
}

void Class::showkecheng3() const 
{
	for (int i = 0;i<MAX;i++)
		sd3[i].showkecheng3();
}

void Class::showsumfenduan() const 
{
	cout << "总成绩90以上的学生: " << "一共" << fenduansumnum[0] << "人" << endl;
	for (int i = 0;i<fenduansumnum[0];i++)
	{
		fenduansum[0][i].showsum();
	}
	cout << "总成绩80到89的学生: " << "一共" << fenduansumnum[1] << "人" << endl;
	for (int i = 0;i<fenduansumnum[1];i++)
	{
		fenduansum[1][i].showsum();	
	} 
	cout << "总成绩70到79的学生: " << "一共" << fenduansumnum[2] << "人" << endl;
	for (int i = 0;i<fenduansumnum[2];i++)
	{
		fenduansum[2][i].showsum();	
	} 
	cout << "总成绩60到69的学生: " << "一共" << fenduansumnum[3] << "人" << endl;
	for (int i = 0;i<fenduansumnum[3];i++)
	{
		fenduansum[3][i].showsum();	
	} 
	cout << "总成绩不及格的学生: " << "一共" << fenduansumnum[4] << "人"  << endl;
	for (int i = 0;i<fenduansumnum[4];i++)
	{
		fenduansum[4][i].showsum();	
	} 
}

void Class::showkecheng1fenduan() const 
{
	cout << "课程" << kecheng1 << " 90以上的学生: " << "一共" << fenduankecheng1num[0] << "人" << endl;
	for (int i = 0;i<fenduankecheng1num[0];i++)
	{
		fenduankecheng1[0][i].showkecheng1();
	}
	cout << "课程" << kecheng1 << " 80到89的学生: " << "一共" << fenduankecheng1num[1] << "人" << endl;
	for (int i = 0;i<fenduankecheng1num[1];i++)
	{
		fenduankecheng1[1][i].showkecheng1();	
	} 
	cout << "课程" << kecheng1 << " 70到79的学生: " << "一共" << fenduankecheng1num[2] << "人" << endl;
	for (int i = 0;i<fenduankecheng1num[2];i++)
	{
		fenduankecheng1[2][i].showkecheng1();	
	} 
	cout << "课程" << kecheng1 << " 60到69的学生: " << "一共" << fenduankecheng1num[3] << "人" << endl;
	for (int i = 0;i<fenduankecheng1num[3];i++)
	{
		fenduankecheng1[3][i].showkecheng1();	
	} 
	cout << "课程" << kecheng1 << " 不及格的学生: " << "一共" << fenduankecheng1num[4] << "人"  << endl;
	for (int i = 0;i<fenduankecheng1num[4];i++)
	{
		fenduankecheng1[4][i].showkecheng1();	
	} 
}

void Class::showkecheng2fenduan() const 
{
	cout << "课程" << kecheng2 << " 90以上的学生: " << "一共" << fenduankecheng2num[0] << "人" << endl;
	for (int i = 0;i<fenduankecheng2num[0];i++)
	{
		fenduankecheng2[0][i].showkecheng(kecheng2);
	}
	cout << "课程" << kecheng2 << " 80到89的学生: " << "一共" << fenduankecheng2num[1] << "人" << endl;
	for (int i = 0;i<fenduankecheng2num[1];i++)
	{
		fenduankecheng2[1][i].showkecheng(kecheng2);	
	} 
	cout << "课程" << kecheng2 << " 70到79的学生: " << "一共" << fenduankecheng2num[2] << "人" << endl;
	for (int i = 0;i<fenduankecheng2num[2];i++)
	{
		fenduankecheng2[2][i].showkecheng(kecheng2);	
	} 
	cout << "课程" << kecheng2 << " 60到69的学生: " << "一共" << fenduankecheng2num[3] << "人" << endl;
	for (int i = 0;i<fenduankecheng2num[3];i++)
	{
		fenduankecheng2[3][i].showkecheng(kecheng2);	
	} 
	cout << "课程" << kecheng2 << " 不及格的学生: " << "一共" << fenduankecheng2num[4] << "人"  << endl;
	for (int i = 0;i<fenduankecheng2num[4];i++)
	{
		fenduankecheng2[4][i].showkecheng(kecheng2);	
	} 
}

void Class::showkecheng3fenduan() const 
{
	cout << "课程" << kecheng3 << " 90以上的学生: " << "一共" << fenduankecheng3num[0] << "人" << endl;
	for (int i = 0;i<fenduankecheng3num[0];i++)
	{
		fenduankecheng3[0][i].showkecheng(kecheng3);
	}
	cout << "课程" << kecheng3 << " 80到89的学生: " << "一共" << fenduankecheng3num[1] << "人" << endl;
	for (int i = 0;i<fenduankecheng3num[1];i++)
	{
		fenduankecheng3[1][i].showkecheng(kecheng3);	
	} 
	cout << "课程" << kecheng3 << " 70到79的学生: " << "一共" << fenduankecheng3num[2] << "人" << endl;
	for (int i = 0;i<fenduankecheng3num[2];i++)
	{
		fenduankecheng3[2][i].showkecheng(kecheng3);	
	} 
	cout << "课程" << kecheng3 << " 60到69的学生: " << "一共" << fenduankecheng3num[3] << "人" << endl;
	for (int i = 0;i<fenduankecheng3num[3];i++)
	{
		fenduankecheng3[3][i].showkecheng(kecheng3);	
	} 
	cout << "课程" << kecheng3 << " 不及格的学生: " << "一共" << fenduankecheng3num[4] << "人"  << endl;
	for (int i = 0;i<fenduankecheng3num[4];i++)
	{
		fenduankecheng3[4][i].showkecheng(kecheng3);	
	} 
}

void Class::chazhaosum(string fenshuduan) const 
{
	if (fenshuduan=="90~100")
	{
		cout << "总成绩 90以上的学生: " << "一共" << fenduansumnum[0] << "人" << endl;
		for (int i = 0;i<fenduansumnum[0];i++)
		{
			fenduansum[0][i].showsum();
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "总成绩80到89的学生: " << "一共" << fenduansumnum[1] << "人" << endl;
		for (int i = 0;i<fenduansumnum[1];i++)
		{
			fenduansum[1][i].showsum();	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "总成绩70到79的学生: " << "一共" << fenduansumnum[2] << "人" << endl;
		for (int i = 0;i<fenduansumnum[2];i++)
		{
			fenduansum[2][i].showsum();	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "总成绩60到69的学生: " << "一共" << fenduansumnum[3] << "人" << endl;
		for (int i = 0;i<fenduansumnum[3];i++)
		{
			fenduansum[3][i].showsum();	
		} 
	}
	else
	{
		cout << "总成绩不及格的学生: " << "一共" << fenduansumnum[4] << "人"  << endl;
		for (int i = 0;i<fenduansumnum[4];i++)
		{
			fenduansum[4][i].showsum();	
		} 
	}
}

void Class::chazhaokecheng1(string fenshuduan) const
{
	if (fenshuduan=="90~100")
	{
		cout << "课程一 90以上的学生: " << "一共" << fenduankecheng1num[0] << "人" << endl;
		for (int i = 0;i<fenduankecheng1num[0];i++)
		{
			fenduankecheng1[0][i].showkecheng1();
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "课程一 80到89的学生: " << "一共" << fenduankecheng1num[1] << "人" << endl;
		for (int i = 0;i<fenduankecheng1num[1];i++)
		{
			fenduankecheng1[1][i].showkecheng1();	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "课程一 70到79的学生: " << "一共" << fenduankecheng1num[2] << "人" << endl;
		for (int i = 0;i<fenduankecheng1num[2];i++)
		{
			fenduankecheng1[2][i].showkecheng1();	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "课程一 60到69的学生: " << "一共" << fenduankecheng1num[3] << "人" << endl;
		for (int i = 0;i<fenduankecheng1num[3];i++)
		{
			fenduankecheng1[3][i].showkecheng1();	
		} 
	}
	else
	{
		cout << "课程一 不及格的学生: " << "一共" << fenduankecheng1num[4] << "人"  << endl;
		for (int i = 0;i<fenduankecheng1num[4];i++)
		{
			fenduankecheng1[4][i].showkecheng1();	
		} 
	}
}

void Class::chazhaokecheng2(string fenshuduan) const 
{
	if (fenshuduan=="90~100")
	{
		cout << "课程二 90以上的学生: " << "一共" << fenduankecheng2num[0] << "人" << endl;
		for (int i = 0;i<fenduankecheng2num[0];i++)
		{
			fenduankecheng2[0][i].showkecheng2();
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "课程二 80到89的学生: " << "一共" << fenduankecheng2num[1] << "人" << endl;
		for (int i = 0;i<fenduankecheng2num[1];i++)
		{
			fenduankecheng2[1][i].showkecheng2();	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "课程二 70到79的学生: " << "一共" << fenduankecheng2num[2] << "人" << endl;
		for (int i = 0;i<fenduankecheng2num[2];i++)
		{
			fenduankecheng2[2][i].showkecheng2();	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "课程二 60到69的学生: " << "一共" << fenduankecheng2num[3] << "人" << endl;
		for (int i = 0;i<fenduankecheng2num[3];i++)
		{
			fenduankecheng2[3][i].showkecheng2();	
		} 
	}
	else
	{
		cout << "课程二 不及格的学生: " << "一共" << fenduankecheng2num[4] << "人"  << endl;
		for (int i = 0;i<fenduankecheng2num[4];i++)
		{
			fenduankecheng2[4][i].showkecheng2();	
		} 
	}
}

void Class::chazhaokecheng3(string fenshuduan) const 
{
	if (fenshuduan=="90~100")
	{
		cout << "课程三 90以上的学生: " << "一共" << fenduankecheng3num[0] << "人" << endl;
		for (int i = 0;i<fenduankecheng3num[0];i++)
		{
			fenduankecheng3[0][i].showkecheng3();
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "课程三 80到89的学生: " << "一共" << fenduankecheng3num[1] << "人" << endl;
		for (int i = 0;i<fenduankecheng3num[1];i++)
		{
			fenduankecheng3[1][i].showkecheng3();	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "课程三 70到79的学生: " << "一共" << fenduankecheng3num[2] << "人" << endl;
		for (int i = 0;i<fenduankecheng3num[2];i++)
		{
			fenduankecheng3[2][i].showkecheng3();	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "课程三 60到69的学生: " << "一共" << fenduankecheng3num[3] << "人" << endl;
		for (int i = 0;i<fenduankecheng3num[3];i++)
		{
			fenduankecheng3[3][i].showkecheng3();	
		} 
	}
	else
	{
		cout << "课程三 不及格的学生: " << "一共" << fenduankecheng3num[4] << "人"  << endl;
		for (int i = 0;i<fenduankecheng3num[4];i++)
		{
			fenduankecheng3[4][i].showkecheng3();	
		} 
	}
}

void Class::tongjisuoyou()
{
	for (int i = 0;i<MAX;i++)
	{
		if (sd[i].sum>=90)
		{
			fenduansumnum[0]++;
			fenduansum[0].push_back(sd[i]);
		}
		else if (sd[i].sum>=80)
		{
			fenduansumnum[1]++;
			fenduansum[1].push_back(sd[i]);
		}
		else if (sd[i].sum>=70)
		{
			fenduansumnum[2]++;
			fenduansum[2].push_back(sd[i]);
		}
		else if (sd[i].sum>=60)
		{
			fenduansumnum[3]++;
			fenduansum[3].push_back(sd[i]);
		}
		else 
		{
			fenduansumnum[4]++;
			fenduansum[4].push_back(sd[i]);
		}             // 统计总成绩情况 
		
		
		if (sd1[i].b[kecheng1]>=90)
		{
			fenduankecheng1num[0]++;
			fenduankecheng1[0].push_back(sd1[i]);
		}
		else if (sd1[i].b[kecheng1]>=80)
		{
			fenduankecheng1num[1]++;
			fenduankecheng1[1].push_back(sd1[i]);
		}
		else if (sd1[i].b[kecheng1]>=70)
		{
			fenduankecheng1num[2]++;
			fenduankecheng1[2].push_back(sd1[i]);
		}
		else if (sd[i].kecheng1>=60)
		{
			fenduankecheng1num[3]++;
			fenduankecheng1[3].push_back(sd1[i]);
		}
		else 
		{
			fenduankecheng1num[4]++;
			fenduankecheng1[4].push_back(sd1[i]);
		}          //统计课程一的成绩情况 
		
		if (sd2[i].b[kecheng2]>=90)
		{
			fenduankecheng2num[0]++;
			fenduankecheng2[0].push_back(sd2[i]);
		}
		else if (sd2[i].b[kecheng2]>=80)
		{
			fenduankecheng2num[1]++;
			fenduankecheng2[1].push_back(sd2[i]);
		}
		else if (sd2[i].b[kecheng2]>=70)
		{
			fenduankecheng2num[2]++;
			fenduankecheng2[2].push_back(sd2[i]);
		}
		else if (sd2[i].b[kecheng2]>=60)
		{
			fenduankecheng2num[3]++;
			fenduankecheng2[3].push_back(sd2[i]);
		}
		else 
		{
			fenduankecheng2num[4]++;
			fenduankecheng2[4].push_back(sd2[i]);
		}          //统计课程二的成绩情况 
		
		if (sd3[i].b[kecheng3]>=90)
		{
			fenduankecheng3num[0]++;
			fenduankecheng3[0].push_back(sd3[i]);
		}
		else if (sd3[i].b[kecheng3]>=80)
		{
			fenduankecheng3num[1]++;
			fenduankecheng3[1].push_back(sd3[i]);
		}
		else if (sd3[i].b[kecheng3]>=70)
		{
			fenduankecheng3num[2]++;
			fenduankecheng3[2].push_back(sd3[i]);
		}
		else if (sd3[i].b[kecheng3]>=60)
		{
			fenduankecheng3num[3]++;
			fenduankecheng3[3].push_back(sd3[i]);
		}
		else 
		{
			fenduankecheng3num[4]++;
			fenduankecheng3[4].push_back(sd3[i]);
		}          //统计课程三的成绩情况 
	}
}

void Class::showsuoyou() const 
{
	for (int i = 0;i<MAX;i++)
	{
		sd[i].showsuoyou();
	}
}

void Class::paixusum(int left,int right)         //排序sd;按照总成绩 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = sd[start].sum1;
	student fuzhiti = sd[start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (sd[end].sum1>x)
			{
				sd[start] = sd[end];
				sd[end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (sd[start].sum1<=x)
			{
				sd[flag] = sd[start];
				sd[start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixusum(left,flag-1);
	paixusum(flag+1,right);
}

void Class::paixukecheng1(int left,int right)  //以课程一的成绩进行排序  排序sd1 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = sd1[start].b[kecheng1];
	student fuzhiti = sd1[start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (sd1[end].b[kecheng1]>x)
			{
				sd1[start] = sd1[end];
				sd1[end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (sd1[start].b[kecheng1]<=x)
			{
				sd1[flag] = sd1[start];
				sd1[start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixukecheng1(left,flag-1);
	paixukecheng1(flag+1,right);
}

void Class::paixukecheng2(int left,int right)  //以课程二的成绩进行排序  排序sd2 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = sd2[start].b[kecheng2];
	student fuzhiti = sd2[start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (sd2[end].b[kecheng2]>x)
			{
				sd2[start] = sd2[end];
				sd2[end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (sd2[start].b[kecheng2]<=x)
			{
				sd2[flag] = sd2[start];
				sd2[start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixukecheng2(left,flag-1);
	paixukecheng2(flag+1,right);
}

void Class::paixukecheng3(int left,int right)  //以课程三的成绩进行排序  排序sd3 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = sd3[start].b[kecheng3];
	student fuzhiti = sd3[start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (sd3[end].b[kecheng3]>x)
			{
				sd3[start] = sd3[end];
				sd3[end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (sd3[start].b[kecheng3]<=x)
			{
				sd3[flag] = sd3[start];
				sd3[start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixukecheng3(left,flag-1);
	paixukecheng3(flag+1,right);
}

void grade::paixusum(int left,int right)         //排序sd;按照总成绩 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = sd[start].sum1;
	student fuzhiti = sd[start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (sd[end].sum1>x)
			{
				sd[start] = sd[end];
				sd[end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (sd[start].sum1<=x)
			{
				sd[flag] = sd[start];
				sd[start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixusum(left,flag-1);
	paixusum(flag+1,right);
}

void grade::showsum() const 
{
	for (int i = 0;i<MAX*10;i++)
		sd[i].showsuoyou();
}

void grade::showfenbanji() const 
{
	for (int i = 1;i<MAXB;i++)
	{
		cout << "B" << i << "班成绩: " << endl;
		c[i].showsum();
		cout << endl;
	}
		
} 

void grade::showzhidingbanji(int i) const 
{
	c[i].showsuoyou();
}

void grade::tongjisuoyou() 
{
	for (int i = 0;i<MAX*10;i++)
	{

		if (sd[i].sum>=90)
		{
			fenduansumnum[0]++;
			fenduansum[0].push_back(sd[i]);
		}
		else if (sd[i].sum>=80)
		{
			fenduansumnum[1]++;
			fenduansum[1].push_back(sd[i]);
		}
		else if (sd[i].sum>=70)
		{
			fenduansumnum[2]++;
			fenduansum[2].push_back(sd[i]);
		}
		else if (sd[i].sum>=60)
		{
			fenduansumnum[3]++;
			fenduansum[3].push_back(sd[i]);
		}
		else 
		{
			fenduansumnum[4]++;
			fenduansum[4].push_back(sd[i]);
		}             // 统计总成绩情况 
		
		if (sd[i].b[sd[i].kecheng1]>=90)
		{
			fenduankechengnum[sd[i].kecheng1][0]++;
			fenduankecheng[sd[i].kecheng1][0].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng1]>=80)
		{
			fenduankechengnum[sd[i].kecheng1][1]++;
			fenduankecheng[sd[i].kecheng1][1].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng1]>=70)
		{
			fenduankechengnum[sd[i].kecheng1][2]++;
			fenduankecheng[sd[i].kecheng1][2].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng1]>=60)
		{
			fenduankechengnum[sd[i].kecheng1][3]++;
			fenduankecheng[sd[i].kecheng1][3].push_back(sd[i]);
		}
		else 
		{
			fenduankechengnum[sd[i].kecheng1][4]++;
			fenduankecheng[sd[i].kecheng1][4].push_back(sd[i]);
		}          //统计课程一的成绩情况 

		if (sd[i].b[sd[i].kecheng2]>=90)
		{
			fenduankechengnum[sd[i].kecheng2][0]++;
			fenduankecheng[sd[i].kecheng2][0].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng2]>=80)
		{
			fenduankechengnum[sd[i].kecheng2][1]++;
			fenduankecheng[sd[i].kecheng2][1].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng2]>=70)
		{
			fenduankechengnum[sd[i].kecheng2][2]++;
			fenduankecheng[sd[i].kecheng2][2].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng2]>=60)
		{
			fenduankechengnum[sd[i].kecheng2][3]++;
			fenduankecheng[sd[i].kecheng2][3].push_back(sd[i]);
		}
		else 
		{
			fenduankechengnum[sd[i].kecheng2][4]++;
			fenduankecheng[sd[i].kecheng2][4].push_back(sd[i]);
		}          //统计课程二的成绩情况 

		if (sd[i].b[sd[i].kecheng3]>=90)
		{
			fenduankechengnum[sd[i].kecheng3][0]++;
			fenduankecheng[sd[i].kecheng3][0].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng3]>=80)
		{
			fenduankechengnum[sd[i].kecheng3][1]++;
			fenduankecheng[sd[i].kecheng3][1].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng3]>=70)
		{
			fenduankechengnum[sd[i].kecheng3][2]++;
			fenduankecheng[sd[i].kecheng3][2].push_back(sd[i]);
		}
		else if (sd[i].b[sd[i].kecheng3]>=60)
		{
			fenduankechengnum[sd[i].kecheng3][3]++;
			fenduankecheng[sd[i].kecheng3][3].push_back(sd[i]);
		}
		else 
		{
			fenduankechengnum[sd[i].kecheng3][4]++;
			fenduankecheng[sd[i].kecheng3][4].push_back(sd[i]);
		}          //统计课程三的成绩情况 
	}
}


void grade::showsumfenduan() const 
{
	cout << "总成绩90以上的学生: " << "一共" << fenduansumnum[0] << "人" << endl;
	for (int i = 0;i<fenduansumnum[0];i++)
	{
		fenduansum[0][i].showsum();
	}
	cout << "总成绩80到89的学生: " << "一共" << fenduansumnum[1] << "人" << endl;
	for (int i = 0;i<fenduansumnum[1];i++)
	{
		fenduansum[1][i].showsum();	
	} 
	cout << "总成绩70到79的学生: " << "一共" << fenduansumnum[2] << "人" << endl;
	for (int i = 0;i<fenduansumnum[2];i++)
	{
		fenduansum[2][i].showsum();	
	} 
	cout << "总成绩60到69的学生: " << "一共" << fenduansumnum[3] << "人" << endl;
	for (int i = 0;i<fenduansumnum[3];i++)
	{
		fenduansum[3][i].showsum();	
	} 
	cout << "总成绩不及格的学生: " << "一共" << fenduansumnum[4] << "人"  << endl;
	for (int i = 0;i<fenduansumnum[4];i++)
	{
		fenduansum[4][i].showsum();	
	} 
}

void grade::showkechengfenduan(int k) const 
{
	cout << "课程" << k << " 90以上的学生: " << "一共" << fenduankechengnum[k][0] << "人" << endl;
	for (int i = 0;i<fenduankechengnum[k][0];i++)
	{
		fenduankecheng[k][0][i].showkecheng(k);
	}
	cout << "课程" << k << " 80到89的学生: " << "一共" << fenduankechengnum[k][1] << "人" << endl;
	for (int i = 0;i<fenduankechengnum[k][1];i++)
	{
		fenduankecheng[k][1][i].showkecheng(k);	
	} 
	cout << "课程" << k << " 70到79的学生: " << "一共" << fenduankechengnum[k][2] << "人" << endl;
	for (int i = 0;i<fenduankechengnum[k][2];i++)
	{
		fenduankecheng[k][2][i].showkecheng(k);	
	} 
	cout << "课程" << k << "  60到69的学生: " << "一共" << fenduankechengnum[k][3] << "人" << endl;
	for (int i = 0;i<fenduankechengnum[k][3];i++)
	{
		fenduankecheng[k][3][i].showkecheng(k);	
	} 
	cout << "课程" << k << "  不及格的学生: " << "一共" << fenduankechengnum[k][4] << "人"  << endl;
	for (int i = 0;i<fenduankechengnum[k][4];i++)
	{
		fenduankecheng[k][4][i].showkecheng(k);	
	} 
}

void grade::chazhaosum(string fenshuduan) const
{
	if (fenshuduan=="90~100")
	{
		cout << "总成绩 90以上的学生: " << "一共" << fenduansumnum[0] << "人" << endl;

		for (int i = 0;i<fenduansumnum[0];i++)
		{
			fenduansum[0][i].showsum();
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "总成绩80到89的学生: " << "一共" << fenduansumnum[1] << "人" << endl;
		for (int i = 0;i<fenduansumnum[1];i++)
		{
			fenduansum[1][i].showsum();	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "总成绩70到79的学生: " << "一共" << fenduansumnum[2] << "人" << endl;
		for (int i = 0;i<fenduansumnum[2];i++)
		{
			fenduansum[2][i].showsum();	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "总成绩60到69的学生: " << "一共" << fenduansumnum[3] << "人" << endl;
		for (int i = 0;i<fenduansumnum[3];i++)
		{
			fenduansum[3][i].showsum();	
		} 
	}
	else
	{
		cout << "总成绩不及格的学生: " << "一共" << fenduansumnum[4] << "人"  << endl;
		for (int i = 0;i<fenduansumnum[4];i++)
		{
			fenduansum[4][i].showsum();	
		} 
	}
}

void grade::chazhaokecheng(string fenshuduan,int k) const 
{
	if (fenshuduan=="90~100")
	{
		cout << "课程" << k << " 90以上的学生: " << "一共" << fenduankechengnum[k][0] << "人" << endl;
		for (int i = 0;i<fenduankechengnum[k][0];i++)
		{
			fenduankecheng[k][0][i].showkecheng(k);
		}
	}
	else if (fenshuduan == "80~89")
	{
		cout << "课程" << k << " 80到89的学生: " << "一共" << fenduankechengnum[k][1] << "人" << endl;
		for (int i = 0;i<fenduankechengnum[k][1];i++)
		{
			fenduankecheng[k][1][i].showkecheng(k);	
		} 
	}
	else if (fenshuduan=="70~79")
	{
		cout << "课程" << k << " 70到79的学生: " << "一共" << fenduankechengnum[k][2] << "人" << endl;
		for (int i = 0;i<fenduankechengnum[k][2];i++)
		{
			fenduankecheng[k][2][i].showkecheng(k);	
		} 
	}
	else if (fenshuduan=="60~69")
	{
		cout << "课程" << k << " 60到69的学生: " << "一共" << fenduankechengnum[k][3] << "人" << endl;
		for (int i = 0;i<fenduankechengnum[k][3];i++)
		{
			fenduankecheng[k][3][i].showkecheng(k);	
		} 
	}
	else
	{
		cout << "课程" << k << " 不及格的学生: " << "一共" << fenduankechengnum[k][4] << "人"  << endl;
		for (int i = 0;i<fenduankechengnum[k][4];i++)
		{
			fenduankecheng[k][4][i].showkecheng(k);	
		} 
	}
}

void grade::chazhaojutistudent(int xuehao) const 
{
	for (int i = 0 ;i<MAX*10;i++)
	{
		if (sd[i].xuehao == xuehao)
		{
			sd[i].showsuoyou();
			return ;
		}
		else 
			continue;
	}
	cout << "查找失败!"; 
}

void grade::showzhidingbanjifenduan(int i,int kecheng) const 
{
	if (i>=MAXB||i<0)
	{
		cout << "输入有误!";
		return ;
	}
	
	if (kecheng==c[i].kecheng1)
		c[i].showkecheng1fenduan();
	else if (kecheng==c[i].kecheng2) 
		c[i].showkecheng2fenduan();
	else if (kecheng==c[i].kecheng3)
		c[i].showkecheng3fenduan();
	else 
		c[i].showsumfenduan();
	
	return ;
}

void grade::ceshixinxi()
{
	srand(int(time(0)));
	for (int i = 1,j = 0;i<MAXB;i++,j++)
	{
		c[i].kecheng1 = j;
		c[i].kecheng2 = (j+1)%kechengnum;
		c[i].kecheng3 = (j+2)%kechengnum;
	}
	
	for (int i = 0,banjix = MAX;i<MAX*10;i++,banjix++)
	{
		sd[i].name = "某人";
		sd[i].xuehao = i+1;
		sd[i].banji = banjix/MAX;
		sd[i].kecheng1 = c[banjix/MAX].kecheng1;
		sd[i].kecheng2 = c[banjix/MAX].kecheng2;
		sd[i].kecheng3 = c[banjix/MAX].kecheng3;
		int suiji = rand()%101;
		while (suiji==0)
			suiji = rand()%101;
			
		int suiji1 = rand()%101;
		while (suiji1==0)
			suiji1 = rand()%101;
			
		int suiji2 = rand()%101;
		while (suiji2==0)
			suiji2 = rand()%101;
		sd[i].b[sd[i].kecheng1] = rand()%101;
		sd[i].b[sd[i].kecheng2] = rand()%101;
		sd[i].b[sd[i].kecheng3] = rand()%101;
		sd[i].returnsum();
		sd[i].returnsum1();
	}
	
	for (int i =1,k = 0;i<MAXB;i++,k+=MAX)
	{
		for (int j = 0;j<MAX;j++)
		{
			c[i].sd[j] = sd[j+k];
			c[i].sd1[j] = sd[j+k];
			c[i].sd2[j] = sd[j+k];
			c[i].sd3[j] = sd[j+k];
		}
	}
	
}

void grade::paixusuoyoubanji()
{
	for (int i =1;i<MAXB;i++)
	{
		c[i].paixukecheng1();
		c[i].paixukecheng2();
		c[i].paixukecheng3();
		c[i].paixusum();
		c[i].tongjisuoyou();
	}
}

void grade::paixukechengfenduan(int a,int b,int left,int right)  //a是课程,b是分段 
{
	if (left>=right)
		return;

	int start = left;
	int end = right;
	int flag= start;
	int x = fenduankecheng[a][b][start].b[a];
	student fuzhiti = fenduankecheng[a][b][start];
	while (start<end)
	{
		for (;end>start;end--)
		{
			if (fenduankecheng[a][b][end].b[a]>x)
			{
				fenduankecheng[a][b][start] = fenduankecheng[a][b][end];
				fenduankecheng[a][b][end] = fuzhiti;
				flag = end;
				break;
			}
		}
		for (;start<end;start++)
		{
			if (fenduankecheng[a][b][start].b[a]<=x)
			{
				fenduankecheng[a][b][flag] = fenduankecheng[a][b][start];
				fenduankecheng[a][b][start] = fuzhiti;
				flag = start;
				break;
			}
		}
	}
	paixukechengfenduan(a,b,left,flag-1);
	paixukechengfenduan(a,b,flag+1,right);
}

void grade::paixusuoyoukechengfenduan()
{
	for (int i =0;i<kechengnum;i++)
		for (int j = 0;j<FenDuan;j++)
			paixukechengfenduan(i,j,0,fenduankechengnum[i][j]-1);
}




int main(void)
{
	grade g;
	g.ceshixinxi();
	g.paixusum();
	g.tongjisuoyou();
	
	g.paixusuoyoubanji();
	g.paixusuoyoukechengfenduan(); //准备就绪
	
	
	g.richengtanxin(); 
	/* 
	g.chazhaojutistudent(1);
	g.chazhaokecheng("dskjf",3);
	g.chazhaosum("dfdf");
	g.showfenbanji();
	g.showkechengfenduan(9);
	g.showsumfenduan();
	g.showzhidingbanji(2);
	g.showzhidingbanjifenduan(2,1);

	g.showsum();*/
}

