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
    
    if (LoanInvestPayment < minPayment) {
        printf("You didn't set aside enough money to pay off our loans. Ending program.");
        exit(0);
    }
    
    printf("Enter your current age: ");
    currentAge = getValidInt(true);
    currentAge = checkNum1(currentAge);

    printf("Enter the age you plan to retire at: ");
    RetireAge = getValidInt(true);
    RetireAge = checkNum2(RetireAge);

    printf("Enter the annual rate of return you predict for your investments: ");
    rateOfReturn = getValidDouble(true);
    rateOfReturn = checkDouble5(rateOfReturn);

    printf("Loan investpayment %lf\n", LoanInvestPayment);

    printf("oweloans %lf\n", oweloans);   

    printf("interestRate %lf\n", interestRate);

    printf("minPayment %lf\n", minPayment);

    printf("currentAge %d\n", currentAge);

    printf("RetireAge %d\n", RetireAge);

    printf("rateOfReturn %lf\n", rateOfReturn);




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
            startingloanPayment = (startingloanPayment * ((rateOfReturn / 12) + 1) + LoanInvestPayment);
        }
    }
    //  MIN LOAN PAYMENT CHECK - WHETHER WE FINISH OUR LOAN WITHIN THE GIVEN TIME OR NOT
    
    Loan_and_minPay_differnce = LoanInvestPayment - minPayment; //  94.68
    startingMinLoan = (oweloans * ((interestRate / 12) + 1) - minPayment);
    newdifference = startingMinLoan - minPayment;
    printf("StartingLoan %lf\n", startingMinLoan);
    for (i = 1, j = 0; i < timeInterval && newdifference > 0; i++, j++) {
        startingMinLoan = (startingMinLoan * ((interestRate / 12) + 1) - minPayment);
        newdifference = startingMinLoan - minPayment;
        printf("%lf\n", startingMinLoan);
    }
    if (i < timeInterval - 1) {
        PreInv = Loan_and_minPay_differnce;
        printf("Investment: %lf\n", PreInv);
        for (i = 0; i < j; i++) {
            PreInv = (PreInv * ((rateOfReturn / 12) + 1) + Loan_and_minPay_differnce);
            printf("%lf\n", PreInv);
        }   
        if (newdifference < 0) {
          LoanWithMinPayment = 0;
          startingMinLoan = ((PreInv * ((rateOfReturn / 12) + 1)) + (LoanInvestPayment - (startingMinLoan * ((interestRate / 12) + 1))));
            printf("STARTING MIN LOAN: %lf\n", startingMinLoan);
            for (NewRemainingTime = i; NewRemainingTime < timeInterval - 2; NewRemainingTime++) {
                startingMinLoan = (startingMinLoan * ((rateOfReturn / 12) + 1) + LoanInvestPayment);
                printf("STARTING MIN LOAN: %lf\n", startingMinLoan);
            }
        }
    }
    else {
        InvestWithMinLoan = Loan_and_minPay_differnce;
        for (i = 1; i < timeInterval; ++i) {  // calculates how much you have in total for investments if you pay the minimum loan for the given interval
            InvestWithMinLoan = (InvestWithMinLoan * ((rateOfReturn / 12) + 1) + Loan_and_minPay_differnce);
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


    // printf("%d\n", i);
    // printf("%d\n", j);
    // PreInv = Loan_and_minPay_differnce;
    // for (i = 0; i < j; i++) {
    //     PreInv = (PreInv * ((rateOfReturn / 12) + 1) + Loan_and_minPay_differnce);
    // }   
    // printf("PREINV: %.5lf\n", PreInv);
    // printf("START: %.5lf\n", startingMinLoan);
    // if (newdifference < 0) {
    //     test = (LoanInvestPayment - (startingMinLoan * ((interestRate / 12) + 1)));
    //     printf("%lf\n", test);
    //     startingMinLoan = ((PreInv * ((rateOfReturn / 12) + 1)) + (LoanInvestPayment - (startingMinLoan * ((interestRate / 12) + 1))));
    //     printf("NEWNEW: %.5lf\n", startingMinLoan);
    //     for (NewRemainingTime = i; NewRemainingTime < timeInterval - 2; NewRemainingTime++) {
    //         startingMinLoan = (startingMinLoan * ((rateOfReturn / 12) + 1) + LoanInvestPayment);
    //     }
    // }
    // printf("startingMinLoan: %.5lf\n", startingMinLoan);
    
    // Final_investment = startingMinLoan;
    // printf("Final investment: %.5lf\n", Final_investment);


    // InvestWithMinLoan = Loan_and_minPay_differnce;

    // for (i = 1; i < timeInterval; ++i) {  // calculates how much you have in total for investments if you pay the minimum loan for the given interval
    //     InvestWithMinLoan = (InvestWithMinLoan * ((rateOfReturn / 12) + 1) + Loan_and_minPay_differnce);
    // }
    
    // ActualLoan = (oweloans * ((interestRate / 12) + 1));
    // LoanWithMinPayment = ActualLoan - minPayment;
    
    // for (i = 1; i < timeInterval; ++i) {  //  calculates how much you have in loans after paying the minimum payment for the given interval
    //     LoanWithMinPayment = (LoanWithMinPayment * ((interestRate / 12) + 1) - minPayment);
    //     if (LoanWithMinPayment < 0 && (timeInterval - i > 0)) {
    //         NewRemainingTime = i;
    //         break;
    //     }
    // }
    // for (i=1; i < NewRemainingTime; ++i) {
    //     InvestWithMinLoan = (InvestWithMinLoan * ((rateOfReturn / 12) + 1) + Loan_and_minPay_differnce);
    // }
    printf("LoanWithMinPayment %lf", LoanWithMinPayment);
    if (LoanWithMinPayment > 0.00) {
      printf("Warning! After you retire you will still have $%.2lf in loans left.\n", LoanWithMinPayment);
    }
    printf("Starting minloan: %lf", startingMinLoan);
    printf("InvestwithminLoan: %lf", InvestWithMinLoan);
    if ((startingMinLoan > 0) && (startingMinLoan < InvestWithMinLoan)) {
        printf("You!!!");
        printf("You should only make the minimum payments on your loan and apply\nthe rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as", startingloanPayment);
        printf(" opposed to $%.2lf if you payed off your loan before investing.", startingMinLoan);
        exit(0);
    }
    if (InvestWithMinLoan > startingloanPayment) {
      printf("You should only make the minimum payments on your loan and apply\nthe rest towards retirement.\n");
      printf("If you do you will have $%.2lf when you retire as", InvestWithMinLoan);
      printf(" opposed to $%.2lf if you payed off your loan before investing.", startingloanPayment);
      exit(0);
    }
    else {
      printf("You should apply all $%.2lf towards your loan before making any investments.\n", LoanInvestPayment);
      printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.", startingloanPayment, startingMinLoan);
      exit(0);
    }
    
    return 0;
}

bool isValidFormat(const int numArgsNeeded, const int numArgsRead, bool isLastElement) {
  char nextChar;
  if (numArgsNeeded != numArgsRead) {
    return false;
  }

  if (isLastElement) {
    scanf("%c", &nextChar); 
    return nextChar == '\n';
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
