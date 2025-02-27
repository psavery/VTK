/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTriangle.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkTriangle
 * @brief   a cell that represents a triangle
 *
 * vtkTriangle is a concrete implementation of vtkCell to represent a triangle
 * located in 3-space.
 */

#ifndef vtkTriangle_h
#define vtkTriangle_h

#include "vtkCell.h"
#include "vtkCommonDataModelModule.h" // For export macro

#include "vtkMath.h" // Needed for inline methods

class vtkLine;
class vtkQuadric;
class vtkIncrementalPointLocator;

class VTKCOMMONDATAMODEL_EXPORT vtkTriangle : public vtkCell
{
public:
  static vtkTriangle* New();
  vtkTypeMacro(vtkTriangle, vtkCell);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Get the edge specified by edgeId (range 0 to 2) and return that edge's
   * coordinates.
   */
  vtkCell* GetEdge(int edgeId) override;

  //@{
  /**
   * See the vtkCell API for descriptions of these methods.
   */
  int GetCellType() override { return VTK_TRIANGLE; }
  int GetCellDimension() override { return 2; }
  int GetNumberOfEdges() override { return 3; }
  int GetNumberOfFaces() override { return 0; }
  vtkCell* GetFace(int) override { return nullptr; }
  int CellBoundary(int subId, const double pcoords[3], vtkIdList* pts) override;
  void Contour(double value, vtkDataArray* cellScalars, vtkIncrementalPointLocator* locator,
    vtkCellArray* verts, vtkCellArray* lines, vtkCellArray* polys, vtkPointData* inPd,
    vtkPointData* outPd, vtkCellData* inCd, vtkIdType cellId, vtkCellData* outCd) override;
  int EvaluatePosition(const double x[3], double closestPoint[3], int& subId, double pcoords[3],
    double& dist2, double weights[]) override;
  void EvaluateLocation(int& subId, const double pcoords[3], double x[3], double* weights) override;
  int Triangulate(int index, vtkIdList* ptIds, vtkPoints* pts) override;
  void Derivatives(
    int subId, const double pcoords[3], const double* values, int dim, double* derivs) override;
  double* GetParametricCoords() override;
  //@}

  /**
   * A convenience function to compute the area of a vtkTriangle.
   */
  double ComputeArea();

  /**
   * Clip this triangle using scalar value provided. Like contouring, except
   * that it cuts the triangle to produce other triangles.
   */
  void Clip(double value, vtkDataArray* cellScalars, vtkIncrementalPointLocator* locator,
    vtkCellArray* polys, vtkPointData* inPd, vtkPointData* outPd, vtkCellData* inCd,
    vtkIdType cellId, vtkCellData* outCd, int insideOut) override;

  /**
   * @deprecated Replaced by vtkTriangle::InterpolateFunctions as of VTK 5.2
   */
  static void InterpolationFunctions(const double pcoords[3], double sf[3]);
  /**
   * @deprecated Replaced by vtkTriangle::InterpolateDerivs as of VTK 5.2
   */
  static void InterpolationDerivs(const double pcoords[3], double derivs[6]);
  //@{
  /**
   * Compute the interpolation functions/derivatives
   * (aka shape functions/derivatives)
   */
  void InterpolateFunctions(const double pcoords[3], double sf[3]) override
  {
    vtkTriangle::InterpolationFunctions(pcoords, sf);
  }
  void InterpolateDerivs(const double pcoords[3], double derivs[6]) override
  {
    vtkTriangle::InterpolationDerivs(pcoords, derivs);
  }
  //@}
  /**
   * Return the ids of the vertices defining edge (`edgeId`).
   * Ids are related to the cell, not to the dataset.
   */
  int* GetEdgeArray(int edgeId);

  /**
   * Plane intersection plus in/out test on triangle. The in/out test is
   * performed using tol as the tolerance.
   */
  int IntersectWithLine(const double p1[3], const double p2[3], double tol, double& t, double x[3],
    double pcoords[3], int& subId) override;

  /**
   * Return the center of the triangle in parametric coordinates.
   */
  int GetParametricCenter(double pcoords[3]) override;

  /**
   * Return the distance of the parametric coordinate provided to the
   * cell. If inside the cell, a distance of zero is returned.
   */
  double GetParametricDistance(const double pcoords[3]) override;

  /**
   * Compute the center of the triangle.
   */
  static void TriangleCenter(
    const double p1[3], const double p2[3], const double p3[3], double center[3]);

  /**
   * Compute the area of a triangle in 3D.
   * See also vtkTriangle::ComputeArea()
   */
  static double TriangleArea(const double p1[3], const double p2[3], const double p3[3]);

  /**
   * Compute the circumcenter (center[3]) and radius squared (method
   * return value) of a triangle defined by the three points x1, x2,
   * and x3. (Note that the coordinates are 2D. 3D points can be used
   * but the z-component will be ignored.)
   */
  static double Circumcircle(
    const double p1[2], const double p2[2], const double p3[2], double center[2]);

  /**
   * Given a 2D point x[2], determine the barycentric coordinates of the point.
   * Barycentric coordinates are a natural coordinate system for simplices that
   * express a position as a linear combination of the vertices. For a
   * triangle, there are three barycentric coordinates (because there are
   * three vertices), and the sum of the coordinates must equal 1. If a
   * point x is inside a simplex, then all three coordinates will be strictly
   * positive.  If two coordinates are zero (so the third =1), then the
   * point x is on a vertex. If one coordinates are zero, the point x is on an
   * edge. In this method, you must specify the vertex coordinates x1->x3.
   * Returns 0 if triangle is degenerate.
   */
  static int BarycentricCoords(const double x[2], const double x1[2], const double x2[2],
    const double x3[2], double bcoords[3]);

  /**
   * Project triangle defined in 3D to 2D coordinates. Returns 0 if
   * degenerate triangle; non-zero value otherwise. Input points are x1->x3;
   * output 2D points are v1->v3.
   */
  static int ProjectTo2D(const double x1[3], const double x2[3], const double x3[3], double v1[2],
    double v2[2], double v3[2]);

  /**
   * Compute the triangle normal from a points list, and a list of point ids
   * that index into the points list.
   */
  static void ComputeNormal(vtkPoints* p, int numPts, const vtkIdType* pts, double n[3]);

  /**
   * Compute the triangle normal from three points.
   */
  static void ComputeNormal(
    const double v1[3], const double v2[3], const double v3[3], double n[3]);

  /**
   * Compute the (unnormalized) triangle normal direction from three points.
   */
  static void ComputeNormalDirection(
    const double v1[3], const double v2[3], const double v3[3], double n[3]);

  // Description:
  // Determine whether or not triangle (p1,q1,r1) intersects triangle
  // (p2,q2,r2). This method is adapted from Olivier Devillers, Philippe Guigue.
  // Faster Triangle-Triangle Intersection Tests. RR-4488, IN-RIA. 2002.
  // <inria-00072100>.
  static int TrianglesIntersect(const double p1[3], const double q1[3], const double r1[3],
    const double p2[3], const double q2[3], const double r2[3]);

  // Description:
  // Given a point x, determine whether it is inside (within the
  // tolerance squared, tol2) the triangle defined by the three
  // coordinate values p1, p2, p3. Method is via comparing dot products.
  // (Note: in current implementation the tolerance only works in the
  // neighborhood of the three vertices of the triangle.
  static int PointInTriangle(const double x[3], const double x1[3], const double x2[3],
    const double x3[3], const double tol2);

  //@{
  /**
   * Calculate the error quadric for this triangle.  Return the
   * quadric as a 4x4 matrix or a vtkQuadric.  (from Peter
   * Lindstrom's Siggraph 2000 paper, "Out-of-Core Simplification of
   * Large Polygonal Models")
   */
  static void ComputeQuadric(
    const double x1[3], const double x2[3], const double x3[3], double quadric[4][4]);
  static void ComputeQuadric(
    const double x1[3], const double x2[3], const double x3[3], vtkQuadric* quadric);
  //@}

protected:
  vtkTriangle();
  ~vtkTriangle() override;

  vtkLine* Line;

private:
  vtkTriangle(const vtkTriangle&) = delete;
  void operator=(const vtkTriangle&) = delete;
};

//----------------------------------------------------------------------------
inline int vtkTriangle::GetParametricCenter(double pcoords[3])
{
  pcoords[0] = pcoords[1] = 1. / 3;
  pcoords[2] = 0.0;
  return 0;
}

//----------------------------------------------------------------------------
inline void vtkTriangle::ComputeNormalDirection(
  const double v1[3], const double v2[3], const double v3[3], double n[3])
{
  double ax, ay, az, bx, by, bz;

  // order is important!!! maintain consistency with triangle vertex order
  ax = v3[0] - v2[0];
  ay = v3[1] - v2[1];
  az = v3[2] - v2[2];
  bx = v1[0] - v2[0];
  by = v1[1] - v2[1];
  bz = v1[2] - v2[2];

  n[0] = (ay * bz - az * by);
  n[1] = (az * bx - ax * bz);
  n[2] = (ax * by - ay * bx);
}

//----------------------------------------------------------------------------
inline void vtkTriangle::ComputeNormal(
  const double v1[3], const double v2[3], const double v3[3], double n[3])
{
  double length;

  vtkTriangle::ComputeNormalDirection(v1, v2, v3, n);

  if ((length = sqrt((n[0] * n[0] + n[1] * n[1] + n[2] * n[2]))) != 0.0)
  {
    n[0] /= length;
    n[1] /= length;
    n[2] /= length;
  }
}

//----------------------------------------------------------------------------
inline void vtkTriangle::TriangleCenter(
  const double p1[3], const double p2[3], const double p3[3], double center[3])
{
  center[0] = (p1[0] + p2[0] + p3[0]) / 3.0;
  center[1] = (p1[1] + p2[1] + p3[1]) / 3.0;
  center[2] = (p1[2] + p2[2] + p3[2]) / 3.0;
}

//----------------------------------------------------------------------------
inline double vtkTriangle::TriangleArea(const double p1[3], const double p2[3], const double p3[3])
{
  double n[3];
  vtkTriangle::ComputeNormalDirection(p1, p2, p3, n);

  return 0.5 * vtkMath::Norm(n);
}

#endif
