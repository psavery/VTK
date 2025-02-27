/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkReebGraphSimplificationFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkReebGraphSimplificationFilter
 * @brief   simplify an input Reeb graph.
 *
 * The filter takes an input vtkReebGraph object and outputs a
 * vtkReebGraph object.
 */

#ifndef vtkReebGraphSimplificationFilter_h
#define vtkReebGraphSimplificationFilter_h

#include "vtkDirectedGraphAlgorithm.h"
#include "vtkFiltersReebGraphModule.h" // For export macro

class vtkReebGraph;
class vtkReebGraphSimplificationMetric;

class VTKFILTERSREEBGRAPH_EXPORT vtkReebGraphSimplificationFilter : public vtkDirectedGraphAlgorithm
{
public:
  static vtkReebGraphSimplificationFilter* New();
  vtkTypeMacro(vtkReebGraphSimplificationFilter, vtkDirectedGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  //@{
  /**
   * Set the persistence threshold for simplification (from 0 to 1).
   * Default value: 0 (no simplification).
   */
  vtkSetMacro(SimplificationThreshold, double);
  vtkGetMacro(SimplificationThreshold, double);
  //@}

  /**
   * Set the persistence metric evaluation code
   * Default value: nullptr (standard topological persistence).
   */
  void SetSimplificationMetric(vtkReebGraphSimplificationMetric* metric);

  vtkReebGraph* GetOutput();

protected:
  vtkReebGraphSimplificationFilter();
  ~vtkReebGraphSimplificationFilter();

  double SimplificationThreshold;

  vtkReebGraphSimplificationMetric* SimplificationMetric;

  int FillInputPortInformation(int portNumber, vtkInformation*) override;
  int FillOutputPortInformation(int, vtkInformation*) override;

  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

private:
  vtkReebGraphSimplificationFilter(const vtkReebGraphSimplificationFilter&) = delete;
  void operator=(const vtkReebGraphSimplificationFilter&) = delete;
};

#endif
