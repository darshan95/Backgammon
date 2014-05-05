#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int not_played_dice2=1,not_played_dice1=1,actual_result[6],max_heuristic=-1000;
int check_bearingoff(int board_state[],int bar_variable_apna)
{
    int i,sum=0;
    for(i=1;i<=18;i++)
    {
        if(board_state[i] > 0)
            break;
    }
    if((i==19) && (bar_variable_apna==0))
        return 1;
    else
        return 0;
}

void print_result()
{
    //printf("not1-- %d not2--- %d actual-- %d\n", not_played_dice1,not_played_dice2,actual_result[5]);
    char a,b,c,d;
    int i;
    if(not_played_dice1==0 && not_played_dice2==1)
    { 
        for(i=0;i<2;i++)
        {
            if(actual_result[i]==-1)
                printf("Z");
            else if(actual_result[i]==-2)
                printf("O");
            else
                printf("%d", actual_result[i]);
            if(i==1)
                printf("\n");
            else
                printf(" ");
        }
        printf("pass\n");

    }
    else if(not_played_dice1==1 && not_played_dice2==0)
    {
        for(i=2;i<4;i++)
        {
            if(actual_result[i]==-1)
                printf("Z");
            else if(actual_result[i]==-2)
                printf("O");
            else
                printf("%d", actual_result[i]);
            if(i==3)
                printf("\n");
            else
                printf(" ");
        }
        printf("pass\n");
    }
    else
    {
        if(actual_result[5] == 1)
        {
            for(i=0;i<=3;i++)
            {
                if(actual_result[i]==-1)
                    printf("Z");
                else if(actual_result[i]==-2)
                    printf("O");
                else
                    printf("%d", actual_result[i]);

                if((i==1) || (i==3))
                    printf("\n");
                else
                    printf(" ");
            }
        }
        else if(actual_result[5]==2)
        {
            for(i=2;i<=3;i++)
            {
                if(actual_result[i]==-1)
                    printf("Z");
                else if(actual_result[i]==-2)
                    printf("O");
                else
                    printf("%d", actual_result[i]);
                if((i==1) || (i==3))
                    printf("\n");
                else
                    printf(" ");
            }
            for(i=0;i<=1;i++)
            {
                if(actual_result[i]==-1)
                    printf("Z");
                else if(actual_result[i]==-2)
                    printf("O");
                else
                    printf("%d", actual_result[i]);
                if((i==1) || (i==3))
                    printf("\n");
                else
                    printf(" ");
            }
        }
    }
}

void implement_bearingoff(int board_state[], int dice, int dice1,int dice2)
{
    int i,j,m,change_occured=0;
    if(dice1==1)
    {
        i=0;
        j=1;
        if(not_played_dice2==1)
            actual_result[5]=1;
    }
    else
    {
        i=2;
        j=3;
        if(not_played_dice1==1)
            actual_result[5]=2;
    }
    if(board_state[25 - dice] > 0)
    {
        actual_result[i] = 25 - dice;
        actual_result[j] = -2;
        change_occured=1;
        if(dice1)
        {
            not_played_dice1 = 0;
        }
        else
        {
            not_played_dice2 = 0;
        }
    }
    else
    {
        for(m=19;m<=23;m++)
        {
            if((board_state[m] > 0) && (board_state[m + dice] >= 0) && ((m+dice)<=24))
            {
                change_occured=1;
                actual_result[i] = m;
                actual_result[j] = m+dice;
                if(dice1)
                    not_played_dice1 = 0;
                else
                    not_played_dice2 = 0;
            }
        }
        if(change_occured==0)
        {
            for(m=19;m<=(25-dice);m++)
            {
                if(board_state[m]!=0)
                {
                    break;
                }
            }
            if(m==(25 - dice + 1))
            {
                for(m=m;m<=24;m++)
                {
                    if(board_state[m] > 0)
                    {
                        change_occured=1;
                        actual_result[i]=m;
                        actual_result[j]=-2;
                        if(dice1)
                            not_played_dice1=0;
                        else
                            not_played_dice2=0;
                        break;
                    }
                }
            }
        }
        if(change_occured==0)
        {
            for(m=19;m<=24;m++)
            {
                if((board_state[m]>0) && (board_state[m + dice] == -1) && ((m+dice)<=24))
                {
                    change_occured=1;
                    actual_result[i] = m;
                    actual_result[j] = m+dice;
                    if(dice1)
                        not_played_dice1 = 0;
                    else
                        not_played_dice2 = 0;
                }
            }
        }
    }
}

int main()
{
        actual_result[5]=0;
        int i,dice[2],bar_variable,bar_variable_dice1,bar_variable_dice2,l,m,k;
        int player[24]={0},after_dice2[25],played_dice2=0,bar_variable_apna,bar_variable_uska;
        int after_dice1[25],played_dice1=0,temp_result[6];
        int temp_heuristic=0,start_heuristic=1;
        char bar[20];
        bar_variable_apna=0;
        bar_variable_uska=0;
        for(i=1;i<=24;i++)
        {
            scanf("%d",&player[i]);
            after_dice1[i] = player[i];
            after_dice2[i] = player[i];
        }
        char c=getchar();
        scanf("%[^\n]",bar);
        if(!((bar[0] >= '0') && (bar[0] <= '9')))
        {
            for(i=0;i<strlen(bar);i++)
            {
                if(bar[i]=='a')
                    bar_variable_apna++;
                if(bar[i]=='b')
                    bar_variable_uska++;
            }
            scanf("%d%d", &dice[0],&dice[1]);
        }
        else
        {
            dice[0] = bar[0] - 48;
            dice[1] = bar[2] - 48;
        }
        while((dice[0] > 6) || (dice[1] > 6) || (dice[1] < 0) || (dice[0] < 0))
        {
            printf("Enter valid outcomes of dice\n");
            scanf("%d%d", &dice[0],&dice[1]);
        }
        int initial_bar = 0;
        int bar_counter = bar_variable_apna,n=0;
        int already_dice1=0,already_dice2=0;

        // If Bar_variable>0
        while(bar_counter>0)
        {
            if(player[dice[0]]==-1 && played_dice1==0)
            {
                player[dice[0]]=1;
                bar_variable_uska+=1;
                bar_variable_apna-=1;
                played_dice1=1;
                already_dice1=1;
                not_played_dice1=0;
                after_dice1[dice[0]] = 1;
                actual_result[0]=-1;
                actual_result[1]=dice[0];
                if(not_played_dice2==1)
                    actual_result[5] = 1;
            }
            else if(player[dice[1]]==-1 && played_dice2==0)
            {
                player[dice[1]]=1;
                bar_variable_uska+=1;
                bar_variable_apna-=1;
                played_dice2=1;
                already_dice2=1;
                not_played_dice2=0;
                after_dice1[dice[1]] = 1;
                actual_result[2]=-1;
                actual_result[3]=dice[1];
                if(not_played_dice1==1)
                    actual_result[5] = 2;
            }
            else if (player[dice[0]]>0 && played_dice1==0)
            {
                player[dice[0]]+=1;
                bar_variable_apna-=1;
                played_dice1=1;
                already_dice1=1;
                not_played_dice1=0;
                actual_result[0]=-1;
                after_dice1[dice[0]] = 1;
                actual_result[1]=dice[0];
                if(not_played_dice2==1)
                {
                    actual_result[5] = 1;
                }
            }
            else if(player[dice[1]]>0 && played_dice2==0)
            {
                player[dice[1]]+=1;
                bar_variable_apna-=1;
                played_dice2=1;
                already_dice2=1;
                not_played_dice2=0;
                after_dice1[dice[1]] = 1;
                actual_result[2]=-1;
                actual_result[3]=dice[1];
                if(not_played_dice1==1)
                    actual_result[5] = 2;
            }
            else if (player[dice[0]]==0 && played_dice1==0)
            {
                player[dice[0]]+=1;
                bar_variable_apna-=1;
                played_dice1=1;
                already_dice1=1;
                not_played_dice1=0;
                actual_result[0]=-1;
                after_dice1[dice[0]] = 1;
                actual_result[1]=dice[0];
                if(not_played_dice2==1)
                {
                    actual_result[5] = 1;
                }
            }
            else if(player[dice[1]]==0 && played_dice2==0)
            {
                player[dice[1]]+=1;
                bar_variable_apna-=1;
                played_dice2=1;
                already_dice2=1;
                not_played_dice2=0;
                after_dice1[dice[1]] = 1;
                actual_result[2]=-1;
                actual_result[3]=dice[1];
                if(not_played_dice1==1)
                    actual_result[5] = 2;
            }
            bar_counter--;
        }
        if(bar_variable_apna>0)
        {
            if(played_dice1==1 && played_dice2==1)
                printf("Z %d\nZ %d\n",actual_result[1],actual_result[3]);
            else if(played_dice1==1 && played_dice2==0)
                printf("Z %d\n pass\n",actual_result[1]);
            else if(played_dice2==1)
                printf("Z %d\n pass\n",actual_result[3]);
            else
                printf("pass\npass\n");
            return 0;
        }
        played_dice1=0,played_dice2=0;
        // if Bearing off condition
        int bearing = check_bearingoff(player,bar_variable_apna);
        if(bearing==1)
        {
            if(already_dice1==0)
                implement_bearingoff(player,dice[0],1,0);
            if(already_dice2==0)
                implement_bearingoff(player,dice[1],0,1);
            print_result();
            return 0; 
        }
        for(m=1;m<25;m++)
        {
            after_dice1[m] = player[m];
        }


        //posible moves
        if(already_dice2==0) 
        {
            for(i=1;i<25;i++)
            {
                bar_variable_dice1 = bar_variable_uska;
                bar_variable_dice2 = bar_variable_uska;
                temp_heuristic=0;
                for(m=1;m<25;m++)
                {
                    after_dice1[m] = player[m];
                }
                bar_variable_dice1 = bar_variable_uska;
                if(player[i]>0)
                {
                    if(already_dice1==0)
                    {
                        if(played_dice1==0)
                        {
                            if((player[i] > 0) && ((i+dice[0])<=24))
                            {
                                // first dice move I
                                if((player[i+dice[0]] >= 0) && (player[i+dice[0]] <=15))
                                {
                                    not_played_dice1=0;
                                    played_dice1=1;
                                    after_dice1[i+dice[0]] += 1;
                                    after_dice2[i+dice[0]] += 1;
                                    after_dice1[i] -= 1;
                                    after_dice2[i] -= 1;
                                    temp_result[0] = i;
                                    temp_result[1] = i+dice[0];
                                    temp_result[4]=0;
                                    if(already_dice2 == 0)
                                        temp_result[5] = 1;
                                }
                                else if(player[i +dice[0]] == -1)
                                {
                                    played_dice1=1;
                                    not_played_dice1=0;
                                    after_dice1[i+dice[0]] = 1;
                                    after_dice2[i+dice[0]] = 1;
                                    after_dice1[i] -= 1;
                                    after_dice2[i] -= 1;
                                    bar_variable_dice1 += 1;
                                    bar_variable_dice2 += 1;
                                    temp_result[0] = i;
                                    temp_result[1] = i+dice[0];
                                    temp_result[4] = bar_variable_dice1;
                                    if(already_dice2 == 0)
                                        temp_result[5] = 1;
              
                                }
                            }
                        }
                    }
                    // second dice move I
                    if((played_dice1==1) || (already_dice1==1))
                    {
                        bearing=check_bearingoff(after_dice1,bar_variable_apna);
                        if(bearing==1)
                        {
                            actual_result[0] = temp_result[0];
                            actual_result[1] = temp_result[1];
                            not_played_dice1=0;
                            actual_result[5]=1;
                            implement_bearingoff(after_dice1,dice[1],0,1);
                            print_result();
                            return 0;
                        }
                        for(m=1;m<25;m++)
                        {
                            after_dice2[m] = after_dice1[m];
                        }
                        played_dice1 = 0;
                        for(k=1;k<25;k++)
                        {
                            bar_variable_dice2 = bar_variable_dice1;
                            temp_result[4] = bar_variable_dice1;
                            for(m=1;m<25;m++)
                            {
                                after_dice2[m] = after_dice1[m];
                            }
                            if((after_dice1[k] > 0) && ((k+dice[1])<=24))
                            {
                                if((after_dice1[k+dice[1]] >= 0) && (after_dice1[k+dice[1]] <=15))
                                {
                                    played_dice2=1;
                                    after_dice2[k+dice[1]] += 1;
                                    after_dice2[k] -= 1;
                                    temp_result[2] = k;
                                    temp_result[3] = k+dice[1];
                                    not_played_dice2=0;
                                }
                                else if(after_dice1[k +dice[1]] == -1)
                                {
                                    played_dice2=1;
                                    after_dice2[k+dice[1]] = 1;
                                    after_dice2[k] -= 1;
                                    bar_variable_dice2 += 1;
                                    temp_result[2] = k;
                                    temp_result[3] = k+dice[1];
                                    temp_result[4] = bar_variable_dice2;
                                    not_played_dice2 = 0;
                                }
                            }
                            // obtain the heuristic value
                            temp_heuristic=0;
                            if(played_dice2==1)
                            {
                                temp_heuristic = 0;
                                played_dice2=0;
                                //opponents bar
                                if(bar_variable_dice2 == 1)
                                {
                                    temp_heuristic += 4;
                                }
                                else if(bar_variable_dice2 > 1)
                                {
                                    temp_heuristic += 6;
                                }
                                for(l=1;l<25;l++)
                                { 
                                    // checking agent's towers
                                    if(after_dice2[l] == 2)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 10;
                                        }
                                        else if((l>=13) && (l<=15))
                                        {
                                            temp_heuristic += 5;
                                        }
                                        else if((l>=16) && (l<=18))
                                        {
                                            temp_heuristic += 6;
                                        }
                                        else if((l>=8) && (l<=12))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=5) && (l<=7))
                                        {
                                            int var3,sum3=0;
                                            for(var3=16;var3<=24;var3++)
                                            {
                                                if(after_dice2[var3] > 0)
                                                    sum3  += after_dice2[var3];
                                            }
                                            if(sum3>=11)
                                            {
                                                temp_heuristic -= 6;
                                            }
                                            else
                                                temp_heuristic += 8;
                                        }
                                        else if((l>=1) && (l<=4))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                    }
                                    else if(after_dice2[l] > 2)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 8;
                                        }
                                        else if((l>=13) && (l<=15))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=16) && (l<=18))
                                        {
                                            temp_heuristic += 5;
                                        }
                                        else if((l>=8) && (l<=12))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=5) && (l<=7))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=1) && (l<=4))
                                        {
                                            temp_heuristic -= 6;
                                        }

                                    }
                                    // Agent's blot
                                    else if(after_dice2[l] == 1)
                                    {
                                        if((l>19) && (l<=24))
                                        {
                                            int var4,variable;
                                            for(var4=19;var4<=24;var4++)
                                            {
                                                if(after_dice2[var4] < 0)
                                                {
                                                    break;
                                                }
                                            }
                                            for(variable=0;variable<=14;variable++)
                                            {
                                                if(after_dice2[variable] > 0)
                                                    break;
                                            }
                                            if((bar_variable_uska == 0) && (var4==25) && (variable==15))
                                                temp_heuristic += 6;
                                            else
                                                temp_heuristic -= 8;
                                        }
                                        else if((l>=15) && (l<=18))
                                        {
                                            temp_heuristic -= 6;

                                        }
                                        else if((l>=8) && (l<=14))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=1) && (l<=7))
                                        {
                                            int var2,sum1=0;
                                            for(var2=16;var2<=24;var2++)
                                            {
                                                if(after_dice2[var2] > 0)
                                                    sum1 += after_dice2[var2];
                                            }
                                            if(sum1 >= 11)
                                            {
                                                temp_heuristic -= 8;
                                            }
                                            else
                                                temp_heuristic += 2;
                                        } 
                                    }


                                    //opponent's towers
                                    else if(after_dice2[l] == -2)
                                    {
                                        if((l>=21) && (l<=24))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=18) && (l<=20))
                                        {
                                            temp_heuristic -= 8;
                                        }
                                        else if((l>=13) && (l<=17))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=7) && (l<=12))
                                        {
                                            temp_heuristic -= 6;
                                        }
                                        else if((l>=1) && (l<=6))
                                        {
                                            temp_heuristic -= 10;
                                        }

                                    }
                                    else if(after_dice2[l] < -2)
                                    {
                                        if((l>=21) && (l<=24))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=18) && (l<=20))
                                        {
                                            temp_heuristic -= 2;
                                        }
                                        else if((l>=13) && (l<=15))
                                        {
                                            temp_heuristic -= 2;
                                        }
                                        else if((l>=7) && (l<=12))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=1) && (l<=6))
                                        {
                                            temp_heuristic -= 8;
                                        }

                                    }

                                    //opponents blot
                                    else if(after_dice2[l] == -1)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=13) && (l<=18))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=9) && (l<=12))
                                        {
                                            temp_heuristic -= 6;
                                        }
                                        else if((l>=1) && (l<=8))
                                        {
                                            temp_heuristic -= 8;
                                        } 
                                    }
                                }
                                 //checking if greater then max_heuristic
                                if(temp_heuristic > max_heuristic)
                                {
                                    max_heuristic=temp_heuristic;
                                    for(m=0;m<6;m++)
                                    {
                                        if(already_dice1==1)
                                        {
                                            if((m==0) || (m==1) || (m==5))
                                                continue;
                                        }
                                        if(already_dice2==1)
                                        {
                                            if((m==2) || (m==3) || (m==5))
                                                continue;
                                        }
                                        actual_result[m] = temp_result[m];
                                    }
                                }
                                temp_heuristic=0;
                            } 
                        }
                    }
                }
            }
        }
      temp_heuristic=0; 
        if(already_dice1==0)
        {
            temp_result[4] = bar_variable_uska;
            for(i=1;i<25;i++)
            {
                for(m=1;m<25;m++)
                {
                    after_dice1[m] = player[m];
                }
                bar_variable_dice1 = bar_variable_uska;
                played_dice2=0;
                for(l=0;l<=3;l++)
                    temp_result[l]=0;
                if(player[i]>0)
                {
                    if(already_dice2==0)
                    {
                        if(played_dice2==0)
                        {
                            if((player[i] > 0) && ((i+dice[1])<=24))
                            {
                                // first dice move I
                                if((player[i+dice[1]] >= 0) && (player[i+dice[1]] <=15))
                                {
                                    played_dice2=1;
                                    after_dice1[i+dice[1]] += 1;
                                    after_dice2[i+dice[1]] += 1;
                                    after_dice1[i] -= 1;
                                    after_dice2[i] -= 1;

                                    temp_result[2] = i;
                                    temp_result[3] = i+dice[1];
                                    temp_result[4]=0;
                                    if(already_dice1==0)
                                        temp_result[5] = 2;

                                }
                                else if(player[i +dice[1]] == -1)
                                {
                                    played_dice2=1;
                                    after_dice1[i+dice[1]] = 1;
                                    after_dice2[i+dice[1]] = 1;
                                    after_dice1[i] -= 1;
                                    after_dice2[i] -= 1;
                                    bar_variable_dice1 += 1;
                                    bar_variable_dice2 += 1;
                                    temp_result[2] = i;
                                    temp_result[3] = i+dice[1];
                                    temp_result[4] = bar_variable_dice1;
                                    if(already_dice1==0)
                                        temp_result[5] = 2;              
                                }
                            }
                        }
                    }
                    // second dice move I
                    if((played_dice2==1) || (already_dice2==1))
                    {
                        bearing=check_bearingoff(after_dice1,bar_variable_apna);
                        if(bearing==1)
                        {
                          //  printf("11111111111111111111111111\n");
                            actual_result[2] = temp_result[2];
                            actual_result[3] = temp_result[3];
                            implement_bearingoff(after_dice1,dice[0],1,0);
                            print_result();
                            return 0;
                        }

                        played_dice2 = 0;
                        for(k=1;k<25;k++)
                        {
                            bar_variable_dice2 = bar_variable_dice1;
                            temp_result[4] = bar_variable_dice1;
                          //  printf("%d\n",after_dice1[16]);
                            for(m=1;m<25;m++)
                            {
                                after_dice2[m] = after_dice1[m];
                            }
                            played_dice1=0;
                            if((after_dice1[k] > 0) && ((k+dice[0])<=24))
                            {
                                if((after_dice1[k+dice[0]] >= 0) && (after_dice1[k+dice[0]] <=15))
                                {
                                    played_dice1=1;
                                    not_played_dice1=0;
                                    after_dice2[k+dice[0]] += 1;
                                    after_dice2[k] -= 1;
                                    temp_result[0] = k;
                                    temp_result[1] = k+dice[0];
                                }
                                else if(after_dice1[k +dice[0]] == -1)
                                {
                                    played_dice1=1;
                                    not_played_dice1=0;
                                    after_dice2[k+dice[0]] = 1;
                                    after_dice2[k] -= 1;
                                    bar_variable_dice2 += 1;
                                    temp_result[0] = k;
                                    temp_result[1] = k+dice[0];
                                    temp_result[4] = bar_variable_dice2;
                                }
                            }
                            // obtain the heuristic value
                            if(played_dice1==1)
                            {
                                played_dice1=0;
                                temp_heuristic = 0;
                                //opponents bar
                                if(bar_variable_dice2 == 1)
                                {
                                    temp_heuristic += 4;
                                }
                                else if(bar_variable_dice2 > 1)
                                {
                                    temp_heuristic += 6;
                                }

                                for(l=1;l<25;l++)
                                { 
                                    // checking agent's towers
                                    if(after_dice2[l] == 2)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 10;
                                        }
                                        else if((l>=13) && (l<=15))
                                        {
                                            temp_heuristic += 6;
                                        }
                                        else if((l>=16) && (l<=18))
                                        {
                                            temp_heuristic += 7;
                                        }
                                        else if((l>=8) && (l<=12))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=5) && (l<=7))
                                        {
                                            int var3,sum3=0;
                                            for(var3=16;var3<=24;var3++)
                                            {
                                                if(after_dice2[var3] > 0)
                                                    sum3  += after_dice2[var3];
                                            }
                                            if(sum3>=12)
                                            {
                                                temp_heuristic -= 6;
                                            }
                                            else
                                                temp_heuristic += 8;
                                        }
                                        else if((l>=1) && (l<=4))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                    }
                                    else if(after_dice2[l] > 2)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 8;
                                        }
                                        else if((l>=13) && (l<=15))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=16) && (l<=18))
                                        {
                                            temp_heuristic += 5;
                                        }

                                        else if((l>=8) && (l<=12))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=5) && (l<=7))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=1) && (l<=4))
                                        {
                                            temp_heuristic -= 6;
                                        }

                                    }
                                    // Agent's blot
                                    else if(after_dice2[l] == 1)
                                    {
                                        if((l>19) && (l<=24))
                                        {
                                            int var4,variable;
                                            for(var4=19;var4<=24;var4++)
                                            {
                                                if(after_dice2[var4] < 0)
                                                {
                                                    break;
                                                }
                                            }
                                            for(variable=0;variable<=14;variable++)
                                            {
                                                if(after_dice2[variable] > 0)
                                                    break;
                                            }
                                            if((bar_variable_uska == 0) && (var4==25) && (variable==15))
                                                temp_heuristic += 6;
                                            else
                                                temp_heuristic -= 8;
                                            //            printf(" l--- %d aaya\n", l);
                                        }
                                        else if((l>=15) && (l<=18))
                                        {
                                            temp_heuristic -= 6;
                                            //          printf(" l--- %d Ghussa\n", l);
                                        }
                                        else if((l>=8) && (l<=14))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=1) && (l<=7))
                                        {
                                            int var2,sum1=0;
                                            for(var2=16;var2<=24;var2++)
                                            {
                                                if(after_dice2[var2] > 0)
                                                    sum1 += after_dice2[var2];
                                            }
                                            //     printf(" l--- %d Ghussa ",temp_heuristic);
                                            if(sum1 >= 11)
                                            {
                                                temp_heuristic -= 8;
                                            }
                                            else
                                                temp_heuristic += 2;
                                        }
                                       /* else if((l>=1) && (l<=4))
                                        {
                                            //     printf(" l--- %d Ghussa ",temp_heuristic);
                                            temp_heuristic += 1;
                                            //  printf(" l--- %d Ghussa ", l);
                                        } */
                                    }


                                    //opponent's towers
                                    else if(after_dice2[l] == -2)
                                    {
                                        if((l>=21) && (l<=24))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=18) && (l<=20))
                                        {
                                            temp_heuristic -= 8;
                                        }
                                        else if((l>=13) && (l<=17))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=7) && (l<=12))
                                        {
                                            temp_heuristic -= 6;
                                        }
                                        else if((l>=1) && (l<=6))
                                        {
                                            temp_heuristic -= 10;
                                        }

                                    }
                                    else if(after_dice2[l] < -2)
                                    {
                                        if((l>=21) && (l<=24))
                                        {
                                            temp_heuristic += 4;
                                        }
                                        else if((l>=18) && (l<=20))
                                        {
                                            temp_heuristic -= 2;
                                        }
                                        else if((l>=13) && (l<=17))
                                        {
                                            temp_heuristic -= 2;
                                        }
                                        else if((l>=7) && (l<=12))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=1) && (l<=6))
                                        {
                                            temp_heuristic -= 8;
                                        }

                                    }

                                    //opponents blot
                                    else if(after_dice2[l] == -1)
                                    {
                                        if((l>=19) && (l<=24))
                                        {
                                            temp_heuristic += 2;
                                        }
                                        else if((l>=13) && (l<=18))
                                        {
                                            temp_heuristic -= 4;
                                        }
                                        else if((l>=9) && (l<=12))
                                        {
                                            temp_heuristic -= 6;
                                        }
                                        else if((l>=1) && (l<=8))
                                        {
                                            temp_heuristic -= 8;
                                        } 
                                    }
                                }
                             //checking if greater then max_heuristic
                                if(temp_heuristic > max_heuristic)
                                {
                                    max_heuristic=temp_heuristic;
                                    for(m=0;m<6;m++)
                                    {
                                        if(already_dice1==1)
                                        {
                                            if((m==0) || (m==1) || (m==5))
                                                continue;
                                        }
                                        if(already_dice2==1)
                                        {
                                            if((m==2) || (m==3) || (m==5))
                                                continue;
                                        }
                                        actual_result[m] = temp_result[m];
                                    }
                                }
                                temp_heuristic=0;
                            } 
                        }
                    }
                }
            }
        }
        print_result();
        return 0;
    }
