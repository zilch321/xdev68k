short int sin_tbl[32][33] =
{
{ 0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0, },
{ 1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1, },
{ 3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3, },
{ 4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4, },
{ 5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5, },
{ 6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6, },
{ 7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7, },
{ 7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7, },
{ 7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7, },
{ 7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7, },
{ 7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7, },
{ 6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6, },
{ 5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5, },
{ 4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4, },
{ 3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3, },
{ 1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1, },
{ 0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0, },
{ -1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1, },
{ -3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3, },
{ -4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4, },
{ -5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5, },
{ -6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6, },
{ -7,-7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7, },
{ -7,-7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7, },
{ -7,-7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7, },
{ -7,-7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7, },
{ -7,-6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7, },
{ -6,-5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6, },
{ -5,-4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5, },
{ -4,-3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4, },
{ -3,-1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3, },
{ -1,0,1,3,4,5,6,7,7,7,7,7,6,5,4,3,1,0,-1,-3,-4,-5,-6,-7,-7,-7,-7,-7,-6,-5,-4,-3,-1, },
};
