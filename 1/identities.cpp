#include<array>

// (xy)z = x(yz)
bool iden1(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                int xy = K[x][y];
                int xyz1 = K[xy][z];

                int yz = K[y][z];
                int xyz2 = K[x][yz];

                res =  xyz1 == xyz2 ? false : true;
                if(res){return res;}
            }

        }

    }
    return res;
}

// xy = yx
bool iden2(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int xy = K[x][y];

            int yx = K[y][x];
            res = xy == yx ? false : true;
            if(res){return res;}
        }
    }
    return res;
}

// x^2y = yx
bool iden3(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int xx = K[x][x];
            int xxy = K[xx][y];

            int xy = K[x][y];
            res = xxy == xy ? false : true;
            if(res){return res;}
        }
        
    }
    return res;
}

// xy^2 = yx
bool iden4(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int yy = K[y][y];
            int xyy = K[x][yy];

            int xy = K[x][y];
            res = xyy == xy ? false : true;
            if(res){return res;}
        }
        
    }
    return res;
}

// (xy)z = (yx)z
bool iden5(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                int xy = K[x][y];
                int xyz = K[xy][z];

                int yx = K[y][x];
                int yxz = K[yx][z];

                res = xyz == yxz ? false : true;
                if(res){return res;}
            }
        
        }
    
    }
    return res;
}

// x(yz) = x(zy)
bool iden6(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                int yz = K[y][z];
                int xyz = K[x][yz];

                int zy = K[z][y];
                int xzy = K[x][zy];

                res = xyz == xzy ? false : true;
                if(res){return res;}
            }
            
        }
        
    }
    return res;
}

// ((xy)z)w = (x(yz))w
bool iden7(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                for(int w = 0; w < 16; w++){
                    int xy = K[x][y];
                    int xyz = K[xy][z];
                    int xyzw = K[xyz][w];
                    
                    int yz = K[y][z];
                    int xyz1 = K[x][yz];
                    int xyzw1 = K[xyz1][w];

                    res = xyzw == xyzw1 ? false : true;
                    if(res){return res;}

                }
                
            }
            
        }
        
    }
    return res;
}

// x((yz)w) = x(y(zw))
bool iden8(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                for(int w = 0; w < 16; w++){
                    int yz = K[y][z];
                    int yzw = K[yz][w];
                    int xyzw = K[x][yzw];
                    
                    int zw = K[z][w];
                    int yzw1 = K[y][zw];
                    int xyzw1 = K[x][yzw1];

                    res = xyzw == xyzw1 ? false : true;
                    if(res){return res;}

                }
                
            }
            
        }
        
    }
    return res;
}

// x((yz)w) = x(y(zw))
bool iden9(std::array<std::array<int,16>,16> K){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int xx = K[x][x];
            int yy = K[y][y];

            int xxyy = K[xx][yy];
            int yyxx = K[yy][xx];
            res = xxyy == yyxx ? false : true;
            if(res){return res;}
        }
        
    }
    return res;
}

// xy ≤ x
bool iden10(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int xy = K[x][y];

            res = O[xy][x] ? false : true;
            if(res){return res;}
        }
        
    }
    return res;
}

// xy ≤ y
bool iden11(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            int xy = K[x][y];

            res = O[xy][y] ? false : true;
            if(res){return res;}
        }
        
    }
    return res;
}

// x ≤ yz ⇒ x ≤ xz
bool quasi1(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){

                int yz = K[y][z];
                int xz = K[x][z];

                bool t1 = O[x][yz] ? true : false;
                bool t2 = O[x][xz] ? true : false;

                res = t1
                ?
                t2 ? false : true
                :
                false;

                if(res){return res;}
            }
            
        }
        
    }
    return res;
}

// x ≤ yz ⇒ x ≤ yx
bool quasi2(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){

                int yz = K[y][z];
                int yx = K[y][x];

                bool t1 = O[x][yz] ? true : false;
                bool t2 = O[x][yx] ? true : false;

                res = t1
                ?
                t2 ? false : true
                :
                false;

                if(res){return res;}
            }
            
        }
        
    }
    return res;
}

// x ≤ yz ∧ x ≤ uw ⇒ x ≤ yw
bool quasi3(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O){
    bool res = false;
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            for(int z = 0; z < 16; z++){
                for(int w = 0; w < 16; w++){
                    for(int u = 0; u < 16; u++){

                        int yz = K[y][z];
                        int uw = K[u][w];
                        int yw = K[y][w];


                        bool t1 = O[x][yz] ? true : false;
                        bool t2 = O[x][uw] ? true : false;
                        bool t3 = O[x][yw] ? true : false;

                        res = (t1 && t2)
                        ?
                        t3 ? false : true
                        :
                        false;
                        if(res){return res;}
                    }

            
                }
        
            }
    
        }

    }
    return res;
}
