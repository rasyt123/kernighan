#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool my_isspace(char c);
int getValidInt(const char* prompt);
double getValidDouble(const char* prompt);
int getValidInt2(const char* prompt, int currentAge);
void checkLoanInvestPayment(double LoanInvestPayment, double minPayment);
double PayOffLoanBeforeInvest(int currentage, int Retireage, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn);
void InvestWithMinPayment(int currentage, int Retireage, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn, double minpayment, bool switchinvest, bool nopayoff, double startingloanpayment);

int main() {
    bool switchinvest;
    bool nopayoff;
    double oweloans, LoanInvestPayment;
    double interestRate, minPayment, rateOfReturn;
    int currentAge, RetireAge;
    double startingloanPayment;

    
  
    switchinvest = false;
    nopayoff = false;
    
    LoanInvestPayment = getValidDouble("Enter how much money you will be putting towards loans/retirement each month: ");
  
    oweloans = getValidDouble("Enter how much you owe in loans: ");
    

    interestRate = getValidDouble("Enter the annual interest rate of the loans: ");
   
    
    minPayment = getValidDouble("Enter your minimum monthly loan payment: ");
    
    checkLoanInvestPayment(LoanInvestPayment, minPayment);
    
    currentAge = getValidInt("Enter your current age: ");


    RetireAge = getValidInt2("Enter the age you plan to retire at: ", currentAge);

    
    rateOfReturn = getValidDouble("Enter the annual rate of return you predict for your investments: ");


    startingloanPayment = PayOffLoanBeforeInvest(currentAge, RetireAge, LoanInvestPayment, oweloans, interestRate, rateOfReturn);
    
    InvestWithMinPayment(currentAge, RetireAge, LoanInvestPayment, oweloans, interestRate, rateOfReturn, minPayment, switchinvest, nopayoff, startingloanPayment);
    
    return 0;
}

void checkLoanInvestPayment(double LoanInvestPayment, double minPayment) {
  if (LoanInvestPayment < minPayment) {
        printf("You didn't set aside enough money to pay off our loans. Ending program.");
        exit(0);
    }
}

double PayOffLoanBeforeInvest(int currentAge, int RetireAge, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn)
{
    int timeInterval, i, remainingTime;
    double startingloanPayment, difference;
    timeInterval = (RetireAge - currentAge) * 12;
    startingloanPayment = (oweloans * ((interestRate / 12) + 1) - LoanInvestPayment);
    difference = startingloanPayment - LoanInvestPayment;
    for (i = 1; i < timeInterval && difference > 0; i++) {
        startingloanPayment = (startingloanPayment * ((interestRate / 12) + 1) - LoanInvestPayment);
        difference = startingloanPayment - LoanInvestPayment;
    }

    if (difference < 0) {
        startingloanPayment = LoanInvestPayment - (startingloanPayment * ((interestRate / 12) + 1));
        for (remainingTime = i; remainingTime < timeInterval - 1; remainingTime++) {
            startingloanPayment = (startingloanPayment * ((rateofreturn / 12) + 1) + LoanInvestPayment);
        }
    }
    return startingloanPayment;
}

void InvestWithMinPayment(int currentage, int Retireage, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn, double minPayment, bool switchinvest, bool nopayoff, double startingloanpayment)
{
    double startingMinLoan, newdifference, PreInv, ActualLoan, LoanWithMinPayment, InvestWithMinLoan = 0, Loan_and_minPay_differnce;
    int i, j, timeInterval, NewRemainingTime;
    timeInterval = (Retireage - currentage) * 12;
    Loan_and_minPay_differnce = LoanInvestPayment - minPayment; //  94.68
    startingMinLoan = (oweloans * ((interestRate / 12) + 1) - minPayment);
    newdifference = startingMinLoan - minPayment;

    for (i = 1, j = 0; i < timeInterval && newdifference > 0; i++, j++) {
        startingMinLoan = (startingMinLoan * ((interestRate / 12) + 1) - minPayment);
        newdifference = startingMinLoan - minPayment;
    }
    if (newdifference < 0) {
      switchinvest = true;
    }
    if (i < timeInterval - 1 && (switchinvest == true)) {
        PreInv = Loan_and_minPay_differnce;
        for (i = 0; i < j; i++) {
            PreInv = (PreInv * ((rateofreturn / 12) + 1) + Loan_and_minPay_differnce);
        }   
        if (newdifference < 0) {
          LoanWithMinPayment = 0;
          startingMinLoan = ((PreInv * ((rateofreturn / 12) + 1)) + (LoanInvestPayment - (startingMinLoan * ((interestRate / 12) + 1))));
            for (NewRemainingTime = i; NewRemainingTime < timeInterval - 2; NewRemainingTime++) {
                startingMinLoan = (startingMinLoan * ((rateofreturn / 12) + 1) + LoanInvestPayment);
            }
        }
    }
    else {
        nopayoff = true;
        InvestWithMinLoan = Loan_and_minPay_differnce;
        for (i = 1; i < timeInterval; ++i) {  // calculates how much you have in total for investments if you pay the minimum loan for the given interval
            InvestWithMinLoan = (InvestWithMinLoan * ((rateofreturn / 12) + 1) + Loan_and_minPay_differnce);
        }
        ActualLoan = (oweloans * ((interestRate / 12) + 1));
        LoanWithMinPayment = ActualLoan - minPayment;
        
        for (i = 1; i < timeInterval; ++i) {  //  calculates how much you have in loans after paying the minimum payment for the given interval
            LoanWithMinPayment = (LoanWithMinPayment * ((interestRate / 12) + 1) - minPayment);
            if (LoanWithMinPayment < 0 && (timeInterval - i > 0)) {
                LoanWithMinPayment = 0;
                NewRemainingTime = i;
                break;
            }
        } 
    }
    if (nopayoff == true) {
      if (LoanWithMinPayment > 0.00) {
        printf("Warning! After you retire you will still have $%.2lf in loans left.\n", LoanWithMinPayment);
      }
      if ((startingMinLoan > 0) && (startingloanpayment < InvestWithMinLoan)) {
        printf("You should only make the minimum payments on your loan and apply\nthe rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as", InvestWithMinLoan);
        printf(" opposed to $%.2lf if you payed off your loan before investing.", startingloanpayment);
        exit(0);
      }
      else {
        printf("You should apply all $%.2lf towards your loan before making any investments.\n", LoanInvestPayment);
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.", startingloanpayment, InvestWithMinLoan);
        exit(0);
      }
    }
    else {
      if (switchinvest == true) {
        if ((startingMinLoan > 0) && (startingloanpayment < startingMinLoan)) {
            printf("You should only make the minimum payments on your loan and apply\nthe rest towards retirement.\n");
            printf("If you do you will have $%.2lf when you retire as", startingMinLoan);
            printf(" opposed to $%.2lf if you payed off your loan before investing.", startingloanpayment);
            exit(0);
        }
        else {
          printf("You should apply all $%.2lf towards your loan before making any investments.\n", LoanInvestPayment);
          printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.", startingloanpayment, startingMinLoan);
          exit(0);
        }
      }
    }
  }

bool my_isspace(char c){
	return c == ' ' || c == '\n' || c == '\t';
}

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); //45  bob  \n
    if(!my_isspace(character)){
      formatIsGood = false;
    }
  }while(character != '\n');
  return formatIsGood;
}

int getValidInt(const char* prompt){
  int num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num); //45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded) || num < 0);

  return num;
}

int getValidInt2(const char* prompt, int currentAge)
{
  int num, RetireAge;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %d", &num); //45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded) || (num <= 0));
  RetireAge = num;
  while (RetireAge < currentAge) {
    do{
      printf("%s", prompt);
      numArgsRead = scanf(" %d", &RetireAge); //45\n
    } while(!isValidFormat(numArgsRead, numArgsNeeded) || (RetireAge <= 0));
  }
  return RetireAge;
}

double getValidDouble(const char* prompt){
  double num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %lf", &num); //45\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded) || (num < 0));

  return num;
}




