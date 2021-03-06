#ifndef MARTRIX3D_H
#define MARTRIX3D_H
#include <math.h>
#include "point3d.h"
namespace geometry {
 class Matrix3D {
    public:
        Matrix3D()
        {
            m_[0][0] = m_[1][1] = m_[2][2] = m_[3][3] = 1.0f;
            m_[0][1] = m_[0][2] = m_[0][3] = 0.0f;
            m_[1][0] = m_[1][2] = m_[1][3] = 0.0f;
            m_[2][0] = m_[2][1] = m_[2][3] = 0.0f;
            m_[3][0] = m_[3][1] = m_[3][2] = 0.0f;
        }
        //add
        friend Matrix3D operator+(const Matrix3D&a,const Matrix3D&b)
        {
            Matrix3D ret;
            int i, j;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    ret.m_[i][j] = a.m_[i][j] + b.m_[i][j];
                }
            }
            return ret;
        }
        //sub
        friend Matrix3D operator-(const Matrix3D&a,const Matrix3D& b)
        {
            Matrix3D ret;
            int i, j;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    ret.m_[i][j] = a.m_[i][j] - b.m_[i][j];
                }
            }
            return ret;
        }

         //mul
        friend Matrix3D operator*(const Matrix3D& a,const Matrix3D& b)
        {
            Matrix3D ret;
            int i, j;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    ret.m_[i][j] = (a.m_[i][0] * b.m_[0][j]) +
                        (a.m_[i][1] * b.m_[1][j]) +
                        (a.m_[i][2] * b.m_[2][j]) +
                        (a.m_[i][3] * b.m_[3][j]);
                }
            }
            return ret;
        }

        bool operator==(const Matrix3D& mat)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (m_[i][j] != mat.m_[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Matrix3D& mat)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (m_[i][j] != mat.m_[i][j])
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        //????????????
        Matrix3D& Scale(float value)
        {
            int i, j;
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                   m_[i][j] * value;
                }
            }
            return *this;
        }
        //?????????
        Matrix3D& Identity() {
            m_[0][0] = m_[1][1] =m_[2][2] = m_[3][3] = 1.0f;
            m_[0][1] = m_[0][2] = m_[0][3] = 0.0f;
            m_[1][0] = m_[1][2] = m_[1][3] = 0.0f;
            m_[2][0] = m_[2][1] = m_[2][3] = 0.0f;
            m_[3][0] =m_[3][1] = m_[3][2] = 0.0f;
            return *this;
        }

        //0?????????
        Matrix3D& Zero() {
            m_[0][0] = m_[0][1] = m_[0][2] = m_[0][3] = 0.0f;
            m_[1][0] = m_[1][1] = m_[1][2] = m_[1][3] = 0.0f;
            m_[2][0] = m_[2][1] = m_[2][2] = m_[2][3] = 0.0f;
            m_[3][0] = m_[3][1] = m_[3][2] = m_[3][3] = 0.0f;
            return *this;
        }

        // //??????????????????
        // Matrix3D SetTranslateMat(float x, float y, float z) {

        //     return matRet;
        // }
        // //??????????????????
        // static Matrix3D GetTranslateMat(float x, float y, float z) {
        //     Matrix3D matRet;
        //     matRet.Identity();
        //     matRet.SetTranslate()
        //     matRet.m[3][0] = x;
        //     matRet.m[3][1] = y;
        //     matRet.m[3][2] = z;
        //     return matRet;
        // }

        // //??????????????????
        // static Matrix GetScaleMat(float x, float y, float z) {
        //     Matrix matRet;
        //     matRet.Identity();
        //     matRet.m[0][0] = x;
        //     matRet.m[1][1] = y;
        //     matRet.m[2][2] = z;
        //     return matRet;
        // }

        // //?????????????????? X?????????
        // // https://blog.csdn.net/csxiaoshui/article/details/65446125
        // static Matrix GetRotateMatX(float x) {
        //     Matrix matRet = GetIdentityMat();//????????????
        //     float SinValue = (float)sin(x);
        //     float CosValue = (float)cos(x);

        //     matRet.m[0][0] = 1; matRet.m[1][0] = 0;            matRet.m[2][0] = 0;            matRet.m[3][0] = 0;
        //     matRet.m[0][1] = 0; matRet.m[1][1] = CosValue;    matRet.m[2][1] = -SinValue; matRet.m[3][1] = 0;
        //     matRet.m[0][2] = 0; matRet.m[1][2] = SinValue;    matRet.m[2][2] = CosValue;    matRet.m[3][2] = 0;
        //     matRet.m[0][3] = 0; matRet.m[1][3] = 0;            matRet.m[2][3] = 0;            matRet.m[3][3] = 1;

        //     return matRet;
        // }

        // //?????????????????? Y?????????
        // // https://blog.csdn.net/csxiaoshui/article/details/65446125
        // static Matrix GetRotateMatY(float y) {
        //     Matrix matRet = GetIdentityMat();//????????????
        //     float SinValue = (float)sin(y);
        //     float CosValue = (float)cos(y);

        //     matRet.m[0][0] = CosValue;    matRet.m[1][0] = 0; matRet.m[2][0] = SinValue;    matRet.m[3][0] = 0;
        //     matRet.m[0][1] = 0;            matRet.m[1][1] = 1;    matRet.m[2][1] = 0;            matRet.m[3][1] = 0;
        //     matRet.m[0][2] = -SinValue;    matRet.m[1][2] = 0;    matRet.m[2][2] = CosValue;    matRet.m[3][2] = 0;
        //     matRet.m[0][3] = 0;            matRet.m[1][3] = 0;    matRet.m[2][3] = 0;            matRet.m[3][3] = 1;

        //     return matRet;
        // }

        // //?????????????????? Z?????????
        // // https://blog.csdn.net/csxiaoshui/article/details/65446125
        // static Matrix GetRotateMatZ(float z) {
        //     Matrix matRet = GetIdentityMat();//????????????
        //     float SinValue = (float)sin(z);
        //     float CosValue = (float)cos(z);

        //     matRet.m[0][0] = CosValue; matRet.m[1][0] = -SinValue; matRet.m[2][0] = 0;    matRet.m[3][0] = 0;
        //     matRet.m[0][1] = SinValue; matRet.m[1][1] = CosValue;  matRet.m[2][1] = 0;    matRet.m[3][1] = 0;
        //     matRet.m[0][2] = 0;           matRet.m[1][2] = 0;           matRet.m[2][2] = 1;    matRet.m[3][2] = 0;
        //     matRet.m[0][3] = 0;           matRet.m[1][3] = 0;           matRet.m[2][3] = 0;    matRet.m[3][3] = 1;

        //     return matRet;
        // }

        // //?????????????????? XYZ?????????
        // static Matrix GetRotateMat(float x, float y, float z)
        // {
        //     //X Y Z???????????? ???????????????????????? ?????????????????????????????? 6??????????????? 2???????????????
        //     Matrix matRet = GetRotateMatX(x).Multipy(GetRotateMatY(y)).Multipy(GetRotateMatZ(z));
        //     return matRet;
        // }

        // //??????LookAt??????
        // //??????????????? ??????????????????????????????????????????????????? ??????????????????
        // // Rx Ry Rz 0
        // // Ux Uy Uz 0
        // // Dx Dy Dz 0
        // // 0  0  0  1 ????????????????????????
        // static Matrix GetLookAtMat(Point3D& camera, Point3D& at, Point3D& up)
        // {
        //     Matrix matRet;
        //     Point3D CameraXAxis, CameraYAxis, CameraZAxis;
        //     CameraZAxis = at.Sub(camera);
        //     CameraZAxis = CameraZAxis.Normalize();
        //     CameraYAxis = up.Normalize();
        //     CameraXAxis = CameraZAxis.CrossProduct(CameraYAxis);
        //     CameraXAxis = CameraXAxis.Normalize();

        //     matRet.m[0][0] = CameraXAxis.x;
        //     matRet.m[1][0] = CameraXAxis.y;
        //     matRet.m[2][0] = CameraXAxis.z;
        //     matRet.m[3][0] = -CameraXAxis.DotProduct(camera);

        //     matRet.m[0][1] = CameraYAxis.x;
        //     matRet.m[1][1] = CameraYAxis.y;
        //     matRet.m[2][1] = CameraYAxis.z;
        //     matRet.m[3][1] = -CameraYAxis.DotProduct(camera);

        //     matRet.m[0][2] = CameraZAxis.x;
        //     matRet.m[1][2] = CameraZAxis.y;
        //     matRet.m[2][2] = CameraZAxis.z;
        //     matRet.m[3][2] = -CameraZAxis.DotProduct(camera);

        //     matRet.m[0][3] = matRet.m[1][3] = matRet.m[2][3] = 0.0f;
        //     matRet.m[3][3] = 1.0f;
        //     return matRet;
        // }

        // //?????????????????? ?????????????????????????????????????????????????????????
        // static Matrix GetPerspectiveMat(float fovy, float aspect, float zn, float zf)
        // {
        //     float fax = 1.0f / (float)tan(fovy * 0.5f);

        //     Matrix matRet = GetZeroMat();
        //     matRet.m[0][0] = (float)(fax / aspect);
        //     matRet.m[1][1] = (float)(fax);
        //     matRet.m[2][2] = zf / (zf - zn);
        //     matRet.m[3][2] = -zn * zf / (zf - zn);
        //     matRet.m[2][3] = 1;
        //     return matRet;
        // }
    private:
        float m_[4][4];

 };
}
#endif
