#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

//init

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

////////////////////////////////////////////////

//static getters functions

int Account::getNbAccounts( void ) { return(_nbAccounts); }

int Account::getTotalAmount( void ) { return(_totalAmount); }

int Account::getNbDeposits( void ) { return(_totalNbDeposits); }

int Account::getNbWithdrawals( void ) { return(_totalNbWithdrawals); }

void Account::displayAccountsInfos( void )
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ";"
    		 << "total:" << getTotalAmount() << ";"
    		 << "deposits:" << getNbDeposits() << ";"
    		 << "withdrawals:" << getNbWithdrawals() << std::endl;
}

void Account::_displayTimestamp( void )
{
	time_t  timer_now;
    tm      *timer_start;
 
    time(&timer_now);
    timer_start = std::localtime(&timer_now);
    std::cout << "[" << timer_start->tm_year + 1900
   			 << std::setw(2) << std::setfill('0') << timer_start->tm_mon + 1
   			 << std::setw(2) << std::setfill('0') << timer_start->tm_mday << "_"
   			 << std::setw(2) << std::setfill('0') << timer_start->tm_hour
   			 << std::setw(2) << std::setfill('0') << timer_start->tm_min
   			 << std::setw(2) << std::setfill('0') << timer_start->tm_sec << "] ";
}

/////////////////////////////////////////////////////////////////////////

//cunstruture and distructure

Account::Account( void ){}

Account::Account(int initial_deposit)
{
	this->_nbAccounts++;
    this->_accountIndex = this->_nbAccounts - 1;
    this->_amount = initial_deposit;
    this->_totalAmount += this->_amount;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;

    this->_displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";"
			 << "amount:" << this->_amount << ";created" << std::endl;
}

Account::~Account( void ) 
{
	 this->_nbAccounts--;

    this->_displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "amount:" << this->_amount << ";closed" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////
//																				//
//								memeber functions								//
//																				//
//////////////////////////////////////////////////////////////////////////////////

int Account::checkAmount()const
{
	return(this->_amount);
}

void Account::makeDeposit(int deposit)
{
	this->_displayTimestamp();
    this->_totalAmount += deposit;
    this->_totalNbDeposits++;
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";
    this->_amount += deposit;
    std::cout << "deposit:" << deposit << ";";
    std::cout << "amount:" << this->_amount << ";" ;
    this->_nbDeposits++;
    std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	 this->_displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";";
    std::cout << "p_amount:" << this->_amount << ";";
    std::cout << "withdrawal:" ;
    if (withdrawal > this->checkAmount())
    {
        std::cout << "refused" << std::endl;
        return (false);
    }
    std::cout << withdrawal << ";" ;
    this->_nbWithdrawals++;
    this->_totalNbWithdrawals++;
    this->_amount -= withdrawal;
    this->_totalAmount -= withdrawal;
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return (true);
}

void Account::displayStatus()const
{
	_displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";"
   				 << "amount:" << this->_amount << ";"
   				 << "deposits:" << this->_nbDeposits << ";"
   				 << "withdrawals:" << this->_nbWithdrawals << std::endl;
}
