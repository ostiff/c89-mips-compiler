int leap_year(int year);

int caller(){
    if(leap_year(2013) == 1)
        return 1;
    else
        return 0;
}

int leap_year(int year){
    if(year%4 == 0){
        if(year%100 == 0){
            if(year%400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}