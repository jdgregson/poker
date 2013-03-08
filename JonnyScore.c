int score(CARD * hand)
{
    /*  return values
    *
    *  0: nothing
    *  1: pair, jacks or better
    *  2: two-pair
    *  3: three-of-a-kind
    *  4: straight
    *  5: flush
    *  6: full house
    *  7: four-of-a-kind
    *  8: straight flush
    *  9: royal flush
    */

    int values[14] = {0};
    int i;
    int flag = 0;
    int isStraight = 0;
    int isFlush = 0;

    // go through the hand and record the cards that we have
    for(i=0;i<5;i++)
    {
        (values[hand[i].face])++;
    }

    // check for flush
    flag = 1;
    for(i=0; i<4; i++)
    {
        if(!(hand[i].suit == hand[i+1].suit))
        {
            flag = 0;
            break;
        }
    }
    if(flag)
    {
        isFlush = 1;
    }

    // check for straight
    flag = 0;
    for(i=1; i<14; i++)
    {
        if(values[i] == 1)
        {
            flag++;
            if(flag == 5)
            {
                break;
            }
        }
        else
        {
            flag = 0;
        }
    }
    if(flag == 5)
    {
        isStraight = 1;
    }

    // check for royal flush
    if(values[1] && values[10] && values[11] && values[12] && values[13])
    {
        if(isFlush)
        {
            return(9);
        }
    }

    // check for straight flush
    if(isStraight && isFlush)
    {
        return(8);
    }

    // check for four-of-a-kind
    for(i=1; i<14; i++)
    {
        if(values[i] == 4)
        {
            return(7);
        }
    }

    // check for full house
    flag = 0;
    for(i=1; i<14; i++)
    {
        if(values[i] == 3 || values[i] == 2)
        {
            flag = values[i];
        }
        if((values[i] == 2 && flag == 3) || (values[i] == 3 && flag == 2))
        {
            return(6);
        }
    }

    // check for flush
    if(isFlush)
    {
        return(5)
    }

    // check for straight
    if(isStraight)
    {
        return(4);
    }

    // check for three-of-a-kind
    for(i=1; i<14; i++)
    {
        if(values[i] == 3)
        {
            return(3);
        }
    }

    // check for two pair
    for(i=1; i<14; i++)
    {
        if(values[i] == 2)
        {
            flag++;
        }
    }
    if(flag > 1)
    {
        return(2);
    }

    // check for Jacks or better and one pair
    if(values[11] || values[12] || values[13])
    {
        for(i=1; i<14; i++)
        {
            if(values[i] == 2)
            {
                return(1);
            }
        }

    }

    return(0);
}
