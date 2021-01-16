Exercise 1-4
main()
{
    float celsius;
    printf("Celsius Farenheit Table\n");
    for (celsius = 0; celsius <= 300; celsius = celsius + 20)
        printf("%3.0f %6.1f\n", celsius, (celsius * 1.8) + 32);
}
