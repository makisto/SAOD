#include <string>
#include <conio.h>
#include <iostream>

using namespace std;

void FixVar(string &fix_var, int &exp, int mant)
{
    while (((mant >> exp) % 2) == 0 && exp >= 0)
    {
        exp--;
    }
    for (int i = 3; i >= 0; i--)
    {
        if(((exp + 1) >> i) % 2 == 1) 
        {
            fix_var += '1';
        } 
		else 
		{
            fix_var += '0';
        }
    }
    fix_var += ' ';
    for (int i = exp - 1; i >= 0; i--)
    {
        if((mant >> i) % 2 == 1)
        {
            fix_var += '1';
        } 
		else 
		{
            fix_var += '0';
        }
    }
};

void Gamma(string &gam_el, int &exp, int mant)
{
    if(mant != 0)
    {
        for (int i = exp; i > 0; i--)
		{							
            gam_el += '0';
        }
        gam_el += ' ';
        gam_el += '1';
        gam_el += ' ';
        for (int i = exp - 1; i >= 0; i--)
        {
            if((mant >> i) % 2 == 1)
            {
                gam_el += '1';
            } 
			else 
			{
                gam_el += '0';
            }
        }
    } 
};

void Omega(string &om_el, int &exp, int mant)
{
    int length;
    string mbuff = " ";
    if(mant != 0)
    {
        om_el = '0';
        length = mant;
        while ((exp + 1) >= 2)
        {
            for (int i = exp; i >= 0; i--)
            {
                if((length >> i) % 2 == 1)
                {
                    mbuff += '1';
                } 
				else 
				{
                    mbuff += '0';
                }
            }
            mbuff += ' ';
            om_el = mbuff + om_el;
            mbuff = ' ';
            length = exp;
            while (((length >> exp) % 2) == 0 && exp >= 0)
            {
                exp--;
        	}
        }
    }
}

int main()
{
	int numbers;
	string fix_var, gam_el, om_el;
	cout << "Количество чисел:" << endl;
	cin >> numbers;
	cout << "Число\tFix + Var\t\tГамма\t\t\tОмега" << endl;
    for(int i = 0; i < numbers; i++)
    {
        cout << i << "\t";
        fix_var = gam_el = om_el = ' ';
        int exp = sizeof(int) * 8 - 1;
        FixVar(fix_var, exp, i);
        cout << fix_var << "\t\t\t";
        Gamma(gam_el, exp, i);
		cout << gam_el << "\t";
        Omega(om_el, exp, i);
		cout << om_el << endl;
    }
	
    return 0;
}
