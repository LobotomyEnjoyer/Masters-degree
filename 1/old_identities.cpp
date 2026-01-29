#include<array>

static bool implication(bool x, bool y)
{
    if((x == true) && (y == false))
        return false;

    return true;
}

// (xy)z = x(yz)
bool i1(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int xy = K[x][y];
                int xyz1 = K[xy][z];

                int yz = K[y][z];
                int xyz2 = K[x][yz];
                
                if(xyz1 != xyz2)
                    return false;
            }
        }
    }
    return true;
}
// xy = yx
bool i2(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];
            int yx = K[y][x];

            if(xy != yx)
                return false;
        }
    }
    return true;
}
// x^2y = xy
bool i3(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xx = K[x][x];
            int xxy = K[xx][y];

            int xy = K[x][y];
            if(xxy != xy)
                return false;
        }
    }
    return true;
}
// xy^2 = xy
bool i4(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int yy = K[y][y];
            int xyy = K[x][yy];

            int xy = K[x][y];

            if(xyy != xy)
                return false;
        }
    }
    return true;
}
// (xy)z = (yx)z
bool i5(std::array<std::array<int,16>,16> K)
{
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

                if(xyz != yxz)
                    return false;
            }
        }
    }
    return true;
}
// x(yz) = x(zy)
bool i6(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int yz = K[y][z];
                int xyz = K[x][yz];

                int zy = K[z][y];
                int xzy = K[x][zy];

                if(xyz != xzy)
                    return false;
            }
        }
    }
    return true;
}
// ((xy)z)w = (x(yz))w
bool i7(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                for(int w = 0; w < 16; w++)
                {
                    int xy = K[x][y];
                    int xyz1 = K[xy][z];
                    int xyzw1 = K[xyz1][w];

                    int yz = K[y][z];
                    int xyz2 = K[x][yz];
                    int xyzw2 = K[xyz2][w];

                    if(xyzw1 != xyzw2)
                        return false;
                }
            }
        }
    }
    return true;
}
// x((yz)w) = x(y(zw))
bool i8(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                for(int w = 0; w < 16; w++)
                {
                    int yz = K[y][z];
                    int yzw1 = K[yz][w];
                    int xyzw1 = K[x][yzw1];

                    int zw = K[z][w];
                    int yzw2 = K[y][zw];
                    int xyzw2 = K[x][yzw2];

                    if(xyzw1 != xyzw2)
                        return false;
                }
            }
        }
    }
    return true;
}
// x^2y^2 = y^2x^2
bool i9(std::array<std::array<int,16>,16> K)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xx = K[x][x];
            int yy = K[y][y];

            int xxyy = K[xx][yy];
            int yyxx = K[yy][xx];

            if(xxyy != yyxx)
                return false;
        }
    }
    return true;
}
// xy ≤ x
bool i10(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            bool O1 = O[xy][x];

            if(!O1)
                return false;
        }
    }
    return true;
}
// xy ≤ y
bool i11(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            int xy = K[x][y];

            bool O1 = O[xy][y];

            if(!O1)
                return false;
        }
    }
    return true;
}
// x ≤ yz ⇒ x ≤ xz
bool qi12(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int yz = K[y][z];
                bool o1 = O[x][yz];

                int xz = K[x][z];
                bool o2 = O[x][xz];

                if(!implication(o1,o2))
                    return false;
            }
        }
    }
    return true;
}
// x ≤ yz ⇒ x ≤ yx
bool qi13(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int yz = K[y][z];
                bool o1 = O[x][yz];

                int yx = K[y][x];
                bool o2 = O[x][yx];

                if(!implication(o1,o2))
                    return false;
            }
        }
    }
    return true;
}
// x ≤ yz ∧ x ≤ uw ⇒ x ≤ yw
bool qi14(std::array<std::array<int,16>,16> K, std::array<std::array<int,16>,16> O)
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                for(int w = 0; w < 16; w++)
                {
                    for(int u = 0; u < 16; u++)
                    {
                        int yz = K[y][z];
                        bool o1 = O[x][yz];

                        int uw = K[u][w];
                        bool o2 = O[x][uw];

                        bool O1 = o1 && o2;

                        int yw = K[y][w];
                        bool O2 = O[x][yw];

                        if(!implication(O1, O2))
                            return false;
                    }
                }
            }
        }
    }
    return true;
}