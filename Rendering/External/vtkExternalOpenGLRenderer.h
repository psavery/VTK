/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkExternalOpenGLRenderer.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkExternalOpenGLRenderer
 * @brief   OpenGL renderer
 *
 * vtkExternalOpenGLRenderer is a secondary implementation of the class
 * vtkOpenGLRenderer. vtkExternalOpenGLRenderer interfaces to the
 * OpenGL graphics library. This class provides API to preserve the color and
 * depth buffers, thereby allowing external applications to manage the OpenGL
 * buffers. This becomes very useful when there are multiple OpenGL applications
 * sharing the same OpenGL context.
 *
 * vtkExternalOpenGLRenderer makes sure that the camera used in the scene if of
 * type vtkExternalOpenGLCamera. It manages light and camera transformations for
 * VTK objects in the OpenGL context.
 *
 * \sa vtkExternalOpenGLCamera
 */

#ifndef vtkExternalOpenGLRenderer_h
#define vtkExternalOpenGLRenderer_h

#include "vtkOpenGLRenderer.h"
#include "vtkRenderingExternalModule.h" // For export macro

// Forward declarations
class vtkLightCollection;
class vtkExternalLight;

class VTKRENDERINGEXTERNAL_EXPORT vtkExternalOpenGLRenderer : public vtkOpenGLRenderer
{
public:
  static vtkExternalOpenGLRenderer* New();
  vtkTypeMacro(vtkExternalOpenGLRenderer, vtkOpenGLRenderer);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Synchronize camera and light parameters
   */
  void Render(void) override;

  /**
   * Create a new Camera sutible for use with this type of Renderer.
   * This function creates the vtkExternalOpenGLCamera.
   */
  vtkCamera* MakeCamera() override;

  /**
   * Add an external light to the list of external lights.
   */
  virtual void AddExternalLight(vtkExternalLight*);

  /**
   * Remove an external light from the list of external lights.
   */
  virtual void RemoveExternalLight(vtkExternalLight*);

  /**
   * Remove all external lights
   */
  virtual void RemoveAllExternalLights();

protected:
  vtkExternalOpenGLRenderer();
  ~vtkExternalOpenGLRenderer() override;

  vtkLightCollection* ExternalLights;

private:
  vtkExternalOpenGLRenderer(const vtkExternalOpenGLRenderer&) = delete;
  void operator=(const vtkExternalOpenGLRenderer&) = delete;
};

#endif // vtkExternalOpenGLRenderer_h
