#include<array>

// если idenN вернёт true - тождество не выполняется
// иначе false
// ЖЕЛАТЕЛЬНО ПОМЕНЯТЬ МЕСТАМИ

// return == false - тождество не выполняется
// return == true - тождество выполняется

// убрать лишнее из кода и упростить его

static bool implication(bool x, bool y)
{
    if((x == true) && (y == false))
        return false;

    return true;
}


// x^2 = x
bool iden1(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        int xx = K[x][x];

        res = xx == x ? true : false;
        if(!res)
            return false;
    }

    return true;
}

// xy = yx
bool iden2(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];
            int yx = K[y][x];

            res = xy == yx ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// x^2*y^2 = y^2*x^2
bool iden3(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xx = K[x][x];
            int yy = K[y][y];

            int xxyy = K[xx][yy];
            int yyxx = K[yy][xx];

            res = xxyy == yyxx ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// x^2*y = xy
bool iden4(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xx = K[x][x];
            int xxy = K[xx][y];

            int xy = K[x][y];

            res = xxy == xy ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// xy = x*y^2
bool iden4_star(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            int yy = K[y][y];
            int xyy = K[x][yy];

            res = xy == xyy ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// xyz = yxz
bool iden5(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int xy = K[x][y];
                int xyz = K[xy][z];

                int yx = K[y][x];
                int yxz = K[yx][z];

                res = xyz == yxz ? true : false;
                if(!res)
                    return false;
            }
        }
    }

    return true;
}

// xyz = xzy
bool iden5_star(std::array<std::array<int,16>,16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int xy = K[x][y];
                int xyz = K[xy][z];

                int xz = K[x][z];
                int xzy = K[xz][y];

                res = xyz == xzy ? true : false;
                if(!res)
                    return false;
            }
        }
    }

    return true;
}

// xy ≤ y
bool iden6(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            res = O[xy][y] ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// xy ≤ x
bool iden6_star(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            res = O[xy][x] ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// xy ≤ y^2
bool iden7(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            int yy = K[y][y];

            res = O[xy][yy] ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// xy ≤ x^2
bool iden7_star(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            int xx = K[x][x];

            res = O[xy][xx] ? true : false;
            if(!res)
                return false;
        }
    }

    return true;
}

// x ≤ yz ⇒ x ≤ yx
bool quasi_iden8(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int yz = K[y][z];
                bool O1 = O[x][yz];

                int yx = K[y][x];
                bool O2 = O[x][yx];

                res = implication(O1, O2) ? true : false;
                if(!res)
                    return false;
            }
        }
    }

    return true;
}

// (x ≤ y^2 ∧ x ≤ z^2) ⇒ x ≤ yz
bool quasi_iden9(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int yy = K[y][y];
                bool o1 = O[x][yy];

                int zz = K[z][z];
                bool o2 = O[x][zz];

                bool O1 = o1 && o2;

                int yz = K[y][z];
                bool O2 = O[x][yz];

                res = implication(O1, O2) ? true : false;
                if(!res)
                    return false;
            }
        }
    }

    return true;
}

// (x ≤ y ∧ x ≤ yz) ⇒ x ≤ y^2
bool quasi_iden10(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                bool o1 = O[x][y];

                int yz = K[y][z];
                bool o2 = O[x][yz];
                bool O1 = o1 && o2;


                int yy = K[y][y];
                bool O2 = O[x][yy];

                res = implication(O1, O2) ? true : false;
                if(!res)
                    return false;
            }
        }
    }

    return true;
}

// (x ≤ y ∧ x ≤ zy) ⇒ x ≤ y^2
bool quasi_iden10_star(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                bool o1 = O[x][y];
                int zy = K[z][y];

                bool o2 = O[x][zy];

                bool O1 = o1 && o2;

                int yy = K[y][y];
                bool O2 = O[x][yy];

                res = implication(O1, O2) ? true : false;
                if(!res)
                    return false;
                
            }
        }
    }

    return true;
}

// (x ≤ yz ∧ x ≤ wv) ⇒ x ≤ yv
bool quasi_iden11(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                for(int v = 0; v < 16; v++)
                {
                    for(int w = 0; w < 16; w++)
                    {
                        int yz = K[y][z];
                        bool o1 = O[x][yz];

                        int wv = K[w][v];
                        bool o2 = O[x][wv];

                        bool O1 = o1 && o2;

                        int yv = K[y][v];
                        bool O2 = O[x][yv];

                        res = implication(O1, O2) ? true : false;
                        if(!res)
                            return false;
                    }
                }
                
            }
        }
    }

    return true;
}