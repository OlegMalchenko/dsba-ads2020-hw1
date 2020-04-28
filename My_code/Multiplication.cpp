

/*WORKSHOP HW1 ADS DSBA, CREATED BY -=MALCHENKO OLEG MAKSIMOVICH=- */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include <ctime>
#include <random>
#include <fstream>



/*NUMBER CLASS*/



class Number
{

public:

	Number() {}
	Number(const std::string& a) : _data(a) {}
	Number(const Number& num) : _data(num._data) {}
	


	std::pair<Number, Number> split(int n) const
	{
		std::pair<Number, Number> res;

		size_t size = _data.size(), splitter = size - (n / 2);

		std::string left, right;

		left = _data.substr(0, splitter);
		right = _data.substr(splitter, size - splitter);

		Number res_first(left);
		Number res_second(right);

		res.first = res_first;
		res.second = res_second;

		return res;
	}



	Number& operator +=(const Number& scnd)
	{

		std::string res_str("");

		std::string str1 = this->_data, str2 = scnd._data;


		str1.erase(0, std::min(str1.find_first_not_of('0'), str1.size() - 1));
		str2.erase(0, std::min(str2.find_first_not_of('0'), str2.size() - 1));

		std::reverse(str1.begin(), str1.end());
		std::reverse(str2.begin(), str2.end());

		if (str1.size() > str2.size())
		{
			std::swap(str1, str2);
		}

		size_t len_1 = str1.size(), len_2 = str2.size();


		int sum_remnant = 0;

		for (size_t i = 0; i < len_1; i++)
		{
			int sum = ((str1[i] - '0') + (str2[i] - '0') + sum_remnant);
			res_str.push_back((sum % 10) + '0');

			sum_remnant = sum / 10;
		}

		for (size_t i = len_1; i < len_2; i++)
		{
			int sum = ((str2[i] - '0') + sum_remnant);
			res_str.push_back((sum % 10) + '0');

			sum_remnant = sum / 10;
		}

		if (sum_remnant != 0)
		{
			res_str.push_back(sum_remnant + '0');
		}

		std::reverse(res_str.begin(), res_str.end());

		this->_data = res_str;

		return *this;

	}



	Number operator +(const Number& scnd) const
	{
		Number res;

		std::string res_str("");

		std::string str1 = _data, str2 = scnd._data;

		
		str1.erase(0, std::min(str1.find_first_not_of('0'), str1.size() - 1));
		str2.erase(0, std::min(str2.find_first_not_of('0'), str2.size() - 1));

		std::reverse(str1.begin(), str1.end());
		std::reverse(str2.begin(), str2.end());

		if (str1.size() > str2.size())
		{
			std::swap(str1, str2);
		}

		size_t len_1 = str1.size(), len_2 = str2.size();


		int sum_remnant = 0;

		for (size_t i = 0; i < len_1; i++)
		{
			int sum = ((str1[i] - '0') + (str2[i] - '0') + sum_remnant);
			res_str.push_back((sum % 10) + '0');

			sum_remnant = sum / 10;
		}

		for (size_t i = len_1; i < len_2; i++)
		{
			int sum = ((str2[i] - '0') + sum_remnant);
			res_str.push_back((sum % 10) + '0');

			sum_remnant = sum / 10;
		}

		if (sum_remnant != 0)
		{
			res_str.push_back(sum_remnant + '0');
		}

		std::reverse(res_str.begin(), res_str.end());

		res._data = res_str;

		return res;

	}



	Number operator -(const Number& scnd) const
	{
		Number res;

		std::string res_str("");

		std::string str1 = scnd._data, str2 = _data;



		std::reverse(str1.begin(), str1.end());
		std::reverse(str2.begin(), str2.end());


		size_t len_1 = str1.size(), len_2 = str2.size();

		int div_remnant = 0;

		for (size_t i = 0; i < len_1; i++)
		{
			int subtr = ((str2[i] - '0') - (str1[i] - '0') - div_remnant);
			if (subtr < 0)
			{
				subtr += 10;
				div_remnant = 1;
			}
			else
			{
				div_remnant = 0;
			}

			res_str.push_back(subtr + '0');
		}

		for (size_t i = len_1; i < len_2; i++)
		{
			int subtr = ((str2[i] - '0') - div_remnant);

			if (subtr < 0)
			{
				subtr += 10;
				div_remnant = 1;
			}
			else
			{
				div_remnant = 0;
			}

			res_str.push_back(subtr + '0');
		}

		std::reverse(res_str.begin(), res_str.end());
		
		res_str.erase(0, std::min(res_str.find_first_not_of('0'), res_str.size()));

		res._data = res_str;

		return res;
	}


	std::string getData() const
	{
		return _data;
	}


	static void makeEqual(Number& num, size_t zeroNum)
	{
		for (size_t i = 0; i < zeroNum; i++)
		{
			num._data = "0" + num._data;
		}
	}
	Number& zeroPowerInserter(size_t i, size_t n)
	{
		for (;_data.size() < n;)
		{
			_data.insert(i, "0");
		}
		return *this;
	}


	size_t size() const
	{
		return _data.size();
	}


	const char operator[] (size_t i) const
	{
		return _data[i];
	}


	const char operator[] (size_t i)
	{
		return _data[i];
	}

private:

	std::string _data;
};
std::ostream& operator<< (std::ostream& out, const Number& num)
{
	out << num.getData();
	return out;
}






/*MULTIPLICATOR CLASS + DERIVED*/









class Multiplicator
{
public:
	virtual Number product(Number num1,Number num2) = 0;
	~Multiplicator() {}
};



using MultVec = std::vector<std::shared_ptr<Multiplicator>>;




class GradeSchoolMult : public Multiplicator
{
	virtual  Number product(Number left_num,Number right_num) override
	{
		Number res;

		size_t size_l = left_num.size(), size_r = right_num.size();

		std::string left = left_num.getData(), right = right_num.getData();

		if (size_l == 0 || size_r == 0 || left == "0" || right == "0")
		{
			Number nullres("0");
			return nullres;
		}
		else
		{

			std::reverse(left.begin(), left.end());	/* aaaaaaaa x bbbbbbbb -> b1*a1+rem+0?+...+a8*b1*/
			std::reverse(right.begin(), right.end());

			enum remnant_arithm { remain, resDigit };

			for (size_t i = 0; i < size_r; i++)
			{
				std::string resulting_step(""), rem_container("");
				int remnant = 0;
				for (size_t j = 0; j < size_l; j++)
				{
					rem_container.append(std::to_string(((right[i] - '0') * (left[j] - '0') + remnant)));
					if (rem_container.size() != 2)
					{
						resulting_step.append(rem_container);
						remnant = 0;
					}
					else
					{
						remnant = rem_container[remain] - '0';
						resulting_step.push_back(rem_container[resDigit]);
					}
					rem_container.clear();
				}

				if (remnant != 0)
				{
					resulting_step.append(std::to_string(remnant));
				}

				resulting_step.insert(0, i, '0');

				std::reverse(resulting_step.begin(), resulting_step.end());

				Number res_step(resulting_step);

				res += res_step;
			}
			return res;
		}
	}
};









class KaratsubaMult : public Multiplicator
{
	virtual Number product(Number left_num,Number right_num) override
	{

		size_t max_size = std::max(left_num.size(), right_num.size());
		
		if (left_num.size() < max_size)
		{
			Number::makeEqual(left_num, max_size - left_num.size());
		}
		else if (right_num.size() < max_size)
		{
			Number::makeEqual(right_num, max_size - right_num.size());
		}
		
		if (max_size == 0)
		{
			Number res("0");
			return res;
		}
		if (max_size == 1)
		{
			Number res(std::to_string((left_num[0] - '0') * (right_num[0] - '0')));
			return res;
		}

		std::pair<Number, Number> left = left_num.split(max_size), right = right_num.split(max_size);



		Number left_left = left.first;
		Number left_right =	left.second;
		Number right_left = right.first;
		Number right_right = right.second;



		Number reS1 = KaratsubaMult::product(left_left, right_left);
		Number reS2 = KaratsubaMult::product(left_right, right_right);
		Number reS3 = KaratsubaMult::product((left_left + left_right), (right_left + right_right));
		Number reS4 = reS3 - (reS1 + reS2);


		reS1 = reS1.zeroPowerInserter(reS1.size(), 2 * (max_size / 2) + reS1.size());
		reS4 = reS4.zeroPowerInserter(reS4.size(), reS4.size() + (max_size / 2));

		Number final_res(reS1 + reS4 + reS2);

		return final_res;
	}

};




class DNCMult : public Multiplicator
{
	virtual Number product(Number left_num, Number right_num) override
	{

		size_t max_size = std::max(left_num.size(), right_num.size());

		if (left_num.size() < max_size)
		{
			Number::makeEqual(left_num, max_size - left_num.size());
		}
		else if (right_num.size() < max_size)
		{
			Number::makeEqual(right_num, max_size - right_num.size());
		}

		if (max_size == 0)
		{
			Number res("0");
			return res;
		}
		if (max_size == 1)
		{
			Number res(std::to_string((left_num[0] - '0') * (right_num[0] - '0')));
			return res;
		}

		std::pair<Number, Number> left = left_num.split(max_size), right = right_num.split(max_size);



		Number left_left = left.first;
		Number left_right = left.second;
		Number right_left = right.first;
		Number right_right = right.second;



		Number reS1 = DNCMult::product(left_left, right_left);
		Number reS2 = DNCMult::product(left_right, right_right);
		Number reS3 = DNCMult::product(left_left, right_right);
		Number reS4 = DNCMult::product(left_right, right_left);
		Number reS5 = reS3 + reS4;


		reS1 = reS1.zeroPowerInserter(reS1.size(), 2 * (max_size / 2) + reS1.size());
		reS5 = reS5.zeroPowerInserter(reS5.size(), reS5.size() + (max_size / 2));

		Number final_res(reS1 + reS5 + reS2);

		return final_res;
	}

};






/*SEPARATE FUNCTIONS, AKA GENERATOR, WRITER & TESTER*/







Number generate(const size_t& length)
{
	std::string res_str("");
	int digit = rand() % 9 + 1;
	res_str += std::to_string(digit);
	for (size_t i = 1; i < length; i++)
	{
		res_str += std::to_string(rand() % 9);
	}
	Number res(res_str);
	return res;
}

void process() //somehow started working incorrectly
{
	std::ofstream output;

	output.open("C:\\Users\\olegm\\OneDrive\\Рабочий стол\\My_ADS_HW\\just_some.csv", std::ios::app);

	MultVec method_storing;

	method_storing.push_back(std::make_shared<GradeSchoolMult>());
	method_storing.push_back(std::make_shared<KaratsubaMult>());
	method_storing.push_back(std::make_shared<DNCMult>());

	enum Methods {GSM, KMA, DNC};

	Number first, second;


	for (size_t i = 1; i <= 10000;)
	{
			output << i << ";";

			clock_t startGSM1, startGSM2, startGSM3, startKB1, startKB2, startKB3, startDNC1, startDNC2, startDNC3;
			clock_t finishGSM1, finishGSM2, finishGSM3, finishKB1, finishKB2, finishKB3, finishDNC1, finishDNC2, finishDNC3;

			first = generate(i);
			second = generate(i);


			startGSM1 = clock();
			Number resGSM1 = method_storing[Methods::GSM]->product(first, second);
			finishGSM1 = clock();

			startGSM2 = clock();
			Number resGSM2 = method_storing[Methods::GSM]->product(first, second);
			finishGSM2 = clock();

			startGSM3 = clock();
			Number resGSM3 = method_storing[Methods::GSM]->product(first, second);
			finishGSM3 = clock();

			output << (((double)(((finishGSM1 - startGSM1) + (finishGSM2 - startGSM2) + (finishGSM3 - startGSM3)) / 3)) / CLOCKS_PER_SEC) << ";";


			startKB1 = clock();
			Number resKB1 = method_storing[Methods::KMA]->product(first, second);
			finishKB1 = clock();

			startKB2 = clock();
			Number resKB2 = method_storing[Methods::KMA]->product(first, second);
			finishKB2 = clock();

			startKB3 = clock();
			Number resKB3 = method_storing[Methods::KMA]->product(first, second);
			finishKB3 = clock();

			output << (((double)(((finishKB1 - startKB1) + (finishKB2 - startKB2) + (finishKB3 - startKB3)) / 3)) / CLOCKS_PER_SEC) << ";";


			startDNC1 = clock();
			Number resDNC1 = method_storing[Methods::DNC]->product(first, second);
			finishDNC1 = clock();

			startDNC2 = clock();
			Number resDNC2 = method_storing[Methods::DNC]->product(first, second);
			finishDNC2 = clock();

			startDNC3 = clock();
			Number resDNC3 = method_storing[Methods::DNC]->product(first, second);
			finishDNC3 = clock();

			output << (((double)(((finishDNC1 - startDNC1) + (finishDNC2 - startDNC2) + (finishDNC3 - startDNC3)) / 3)) / CLOCKS_PER_SEC) << "\n";

			if (i >= 1000)
			{
				i += 100;
			}
			else
			{
				i += 1;
			}
	}
	
	output.close();
}








int main()
{
	std::string name, answer;
	std::cout << "Please, enter your name: ";
	std::cin >> name;
	std::cout << "\nHello, " << name << ", please type 'process' to start putting the data into the file, or type any other word so that to exit the program. Please, double-check, that the path to the folder to which your file would be put is defined correctly in the 'process()' function!\n\n";
	std::cin >> answer;
	if (answer == "process")
	{
		std::cout << "\nProcess started!\n\n";
		std::cout << "Please, wait :) \n\n";
		process();
		std::cout << "Done!\n";
		return 0;
	}
	else
	{
		std::cout << "\nBye, " << name << "!\n";
		return 0;
	}
}
/*
	ADS 
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Can Be found at: https://github.com/OlegMalchenko/dsba-ads2020-hw1

	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/