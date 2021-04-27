
int f(){

    int x = 5;

    switch(10){
        case(10) :
            switch(12){
                case(12) :
                    switch(13) {
                        case(11) :{
                            int x = 23;
                            return x;
                        }
                        case(13) :
                            x = 13;
                            break;
                    }
            }
    }
    return x;
}