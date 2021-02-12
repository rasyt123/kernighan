#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

bool isValidFormat(const int numArgsNeeded, const int numArgsRead, bool isLastElement);
int getValidInt(const bool isLastElementOnLine);
double getValidDouble(const bool isLastElementOnLine);
double checkDouble1(double num);
double checkDouble2(double num);
double checkDouble3(double num);
double checkDouble4(double num);
double checkDouble5(double num);
int checkNum1(int num);
int checkNum2(int num);
void checkLoanInvestPayment(double LoanInvestPayment, double minPayment);
double PayOffLoanBeforeInvest(int currentage, int Retireage, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn);
void InvestWithMinPayment(int currentage, int Retireage, double LoanInvestPayment, double oweloans, double interestRate, double rateofreturn, double minpayment, bool switchinvest, bool nopayoff, double startingloanpayment);

int main() {
    bool switchinvest;
    bool nopayoff;
    int i;
    int j;
    double test;
    double PreInv;
    double Final_investment;
    double startingMinLoan = 0;
    double newdifference;
    double oweloans, LoanInvestPayment;
    double interestRate, minPayment, rateOfReturn;
    int currentAge, RetireAge;
    int timeInterval;
    double minLoanRestInvest;
    double startingloanPayment;
    double InvestWithMinLoan;
    double Loan_and_minPay_differnce;
    int remainingTime;
    int NewRemainingTime;
    double ActualLoan;
    double LoanWithMinPayment;
    double difference;
  
    switchinvest = false;
    nopayoff = false;
    
    printf("Enter how much money you will be putting towards loans/retirement each month: ");
    LoanInvestPayment = getValidDouble(true);
    LoanInvestPayment = checkDouble1(LoanInvestPayment);

    printf("Enter how much you owe in loans: ");
    oweloans = getValidDouble(true);
    oweloans = checkDouble2(oweloans);

    printf("Enter the annual interest rate of the loans: ");
    interestRate = getValidDouble(true);
    interestRate = checkDouble3(interestRate);
    
    printf("Enter your minimum monthly loan payment: ");
    minPayment = getValidDouble(true);
    minPayment = checkDouble4(minPayment);
    
    checkLoanInvestPayment(LoanInvestPayment, minPayment);
    
    printf("Enter your current age: ");
    currentAge = getValidInt(true);
    currentAge = checkNum1(currentAge);

    printf("Enter the age you plan to retire at: ");
    RetireAge = getValidInt(true);
    RetireAge = checkNum2(RetireAge);

    printf("Enter the annual rate of return you predict for your investments: ");
    rateOfReturn = getValidDouble(true);
    rateOfReturn = checkDouble5(rateOfReturn);
    timeInterval = (RetireAge - currentAge) * 12;
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
    double Loan_and_minPay_difference, startingMinLoan, newdifference, PreInv, ActualLoan, LoanWithMinPayment, InvestWithMinLoan, Loan_and_minPay_differnce;
    int i, j, timeInterval, remainingtime, NewRemainingTime;
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


bool isValidFormat(const int numArgsNeeded, const int numArgsRead, bool isLastElement) {
  char nextChar;
  if (numArgsNeeded != numArgsRead) {
    return false;
  }

  if (isLastElement) {
    scanf("%c", &nextChar); 
    return nextChar == '\n' || nextChar == '\t' || nextChar == ' ';
  } else {
    return true;
  }

}

int getValidInt(const bool isLastElementOnLine) 
{
  const int numArgsNeeded = 1;
  int numArgsRead;
  int num;

  numArgsRead = scanf(" %d", &num);
  if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    if (num < 0) {
        return 1;
    }
    else {
        return num;
    }
  } else {
    return 0;
  }
}

double getValidDouble(const bool isLastElementOnLine) 
{
  const int numArgsNeeded = 1;
  int numArgsRead;
  double num;

  numArgsRead = scanf(" %lf", &num);
  if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    if (num < 0) {
        return 1;
    }
    else {
        return num;
    }
  } else {
    return 0;
  }
}

double checkDouble1(double num) 
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter how much money you will be putting towards loans/retirements each month: ");
      num = getValidDouble(true);
    }
  return num;
}

double checkDouble2(double num) 
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter how much you owe in loans: ");
      num = getValidDouble(true);
    }
  return num;
}

double checkDouble3(double num) 
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter the annual interest rate of the loans: ");
      num = getValidDouble(true);
    }
  return num;
}

double checkDouble4(double num) 
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter your minimum monthly loan payment: ");
      num = getValidDouble(true);
    }
  return num;
}

double checkDouble5(double num) 
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter the annual rate of return you predict for your investments: ");
      num = getValidDouble(true);
    }
  return num;
}

int checkNum1(int num)
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter your current age: ");
      num = getValidInt(true);
    }
  return num;
}

int checkNum2(int num)
{
  char c;
  while (num == 0 || num == 1) {
      while (true && (num != 1)) {
          scanf("%c", &c);
          if (c == '\n') {
            break;
          }
        }
      printf("Enter the age you plan to retire at: ");
      num = getValidInt(true);
    }
  return num;
}
