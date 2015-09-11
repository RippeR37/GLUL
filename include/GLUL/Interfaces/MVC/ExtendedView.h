#pragma once

#include <GLUL/Interfaces/MVC/View.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>


namespace GLUL {

    namespace Interface {

        namespace MVC {

            /***
             * Template class of extended view where type T is view's assigned model
             */
            template<typename T>
            class GLUL_API ExtendedView : public View<T> {
                public:
                    virtual ~ExtendedView() {
                
                    }
            
                    virtual void init(const T& object) {
                        initVBO(object);
                        initVAO();
                    }

                protected:
                    virtual void initVAO() {
                        _vao.bind();
                        _vao.setAttribPointers();
                        _vao.unbind();
                    }

                    virtual void initVBO(const T& object) {
                        _vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
                        _vbo.setTarget(GL::VertexBuffer::Target::Array);

                        _vbo.bind();
                            setVertexData(object);
                        _vbo.unbind();
                    }

                    virtual void setVertexData(const T& object) = 0;

                    unsigned int _drawCount;
                    GL::Program _program;
                    GL::VertexArray _vao;
                    GL::VertexBuffer _vbo;
            };


            /***
             * Template specialization of extended view for views without models
             */
            template<>
            class GLUL_API ExtendedView<void> : public View<void> {
                public:
                    virtual ~ExtendedView() {

                    }
            
                    virtual void init() {
                        initVBO();
                        initVAO();
                    }

                protected:
                    virtual void initVAO() {
                        _vao.bind();
                        _vao.setAttribPointers();
                        _vao.unbind();
                    }

                    virtual void initVBO() {
                        _vbo.bind();
                            setVertexData();
                        _vbo.unbind();
                    }

                    virtual void setVertexData() = 0;

                    unsigned int _drawCount;
                    GL::Program _program;
                    GL::VertexArray _vao;
                    GL::VertexBuffer _vbo;
            };

        }

    }

}
