/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inv_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:46:30 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/02 15:46:30 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



/*float determinant(t_matrix4x4 matrix)
{
	int c;
	float det = 0, s = 1;
	float b[3][3];
	int i, j;
	int m, n;

	if (sizeof(matrix.matrix) / sizeof(matrix.matrix[0]) == 1)
	    return (matrix.matrix[0][0]);
	det = 0;
	for (c = 0; c < sizeof(matrix.matrix) / sizeof(matrix.matrix[0]); c++)
	{
		m = 0;
		n = 0;
		for (i = 1; i < sizeof(matrix.matrix) / sizeof(matrix.matrix[0]); i++)
		{
			for (j = 0; j < sizeof(matrix.matrix) / sizeof(matrix.matrix[0]); j++)
			{
				b[i - 1][j] = 0;
				if (j != c)
				{
					b[m][n] = matrix.matrix[i][j];
					if (n < (sizeof(matrix.matrix) / sizeof(matrix.matrix[0])) - 2)
					{
						n++;
					}
					else
					{
						n = 0;
						m++;
					}
				}
			}
		}
		det = det + s * (matrix.matrix[0][c] * determinant(b));
		s = -1 * s;
	}
	return (det);
}

t_matrix4x4 cofactor(t_matrix4x4 matrix, t_matrix4x4 cofactorMatrix)
{
    int p, q, m, n, i, j;
    float submatrix[4][4];

    for (p = 0; p < 4; p++)
    {
        for (q = 0; q < 4; q++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    if (i != p && j != q)
                    {
                        submatrix[m][n] = matrix.matrix[i][j];
                        if (n < 2)
                        {
                            n++;
                        }
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            cofactorMatrix.matrix[p][q] = pow(-1, p + q) * determinant(submatrix, size - 1);
        }
    }
	return (cofactorMatrix);
}

t_matrix4x4 adjoint(t_matrix4x4 matrix)
{
    int i, j;
	t_matrix4x4 adjointMatrix;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            adjointMatrix.matrix[i][j] = matrix.matrix[j][i];
        }
    }
	return (adjointMatrix);
}

t_matrix4x4 inverse(t_matrix4x4 matrix)
{
    int i, j;
	t_matrix4x4 inverseMatrix;
    float det = determinant(matrix.matrix, size);

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            inverseMatrix.matrix[i][j] = matrix.matrix[i][j] / det;
        }
    }
	return (inverseMatrix);
}

t_matrix4x4 matrixInverse(t_matrix4x4 matrix)
{
    int size = 4;
    float det = determinant(matrix.matrix, size);
    printf("\nThe determinant of the matrix is %f", det);
    if (det == 0)
    {
        printf("\nMatrix is not invertible.\n");
        return (init_mat_0());
    }
    t_matrix4x4 cofactorMatrix = cofactor(matrix, cofactorMatrix);
    t_matrix4x4 adjointMatrix = adjoint(cofactorMatrix);
    t_matrix4x4 inverseMatrix = inverse(adjointMatrix);
	return (inverseMatrix);
}*/




float determinent(float matrix[25][25], float size)
{
    int c;
    float det=0,s=1;
    float b[25][25];
    int i,j;
    int m,n;
    if(size == 1)
    {
        return (matrix[0][0]);
    }
    else
    {
        det=0;
        for(c=0; c<size; c++)
        {
            m=0;
            n=0;
            for(i=0; i<size; i++)
            {
                for(j=0; j<size; j++)
                {
                    b[i][j] = 0;
                    if(i!=0 && j!=c)
                    {
                        b[m][n] = matrix[i][j];
                        if(n<(size-2))
                        {
                            n++;
                        }
                        else
                        {
                            n=0;
                            m++;
                        }
                    }
                }
            }
            det = det + s*(matrix[0][c]*determinent(b,size-1));
            s = -1*s;
        }
    }
    return (det);
}

t_matrix4x4 matrixInverse(t_matrix4x4 matrices, int len)
{
	float k;
	k = len;
	int i,j;
	float matrix[25][25];
	for(i=0; i<k; i++)
	{
		for(j=0; j<k; j++)
		{
			matrix[i][j] = matrices.matrix[i][j];
		}
	}
	float result = determinent(matrix,k);
	//printf("\nThe determinant of the matrix is %f",result);
	float cofactor[25][25];
	if(result == 0)
		return init_mat_0();
	int c,d,p,q;
	int m,n;
	int size = k;
	float b[25][25];
	for(c=0; c<size; c++)
	{
		for(d=0; d<size; d++)
		{
			m=0;
			n=0;
			for(p=0; p<size; p++)
			{
				for(q=0; q<size; q++)
				{
					if(p!=c && q!=d)
					{
						b[m][n] = matrix[p][q];
						if(n<(size-2))
						{
							n++;
						}
						else
						{
							n=0;
							m++;
						}
					}
					cofactor[c][d] = pow(-1,c+d)*determinent(b,k-1);
				}
			}
		}
	 }
	float Adjoint[25][25];
	int s,t;
	for(s=0; s<k; s++)
	{
		//printf("\n");
		for(t=0; t<k; t++)
		{
			Adjoint[s][t] = cofactor[t][s];
		}
	}
	float Inverse[25][25];
	int l,z;
	for(l=0; l<k; l++)
	{
		for(z=0; z<k; z++)
		{
			Inverse[l][z] = (Adjoint[l][z])/result;
		}
	}
	int e,f;
	//printf("The inverse of the matrix is");
	for(e=0; e<k; e++)
	{
		//printf("\n");
		for(f=0; f<k; f++)
		{
			//printf("%f ",Inverse[e][f]);
			matrices.matrix[e][f] = Inverse[e][f];
		}
	}
	//printf("\n");
	return (matrices);
}
