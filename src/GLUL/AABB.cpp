#include <GLUL/AABB.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>


namespace GLUL {

    AABB::AABB() : AABB(glm::vec3(0.0f), glm::vec3(0.0f)) {

    }

    AABB::AABB(const glm::vec3& min, const glm::vec3& max) {
        setMin(min);
        setMax(max);
        _initialized = false;
    }

    void AABB::clear() {
        setMin(glm::vec3(0.0f));
        setMax(glm::vec3(0.0f));
        _initialized = false;
    }

    bool AABB::intersect(const AABB& box2) const {
        bool result;

        result = AABB::intersect(*this, box2);

        return result;
    }

    void AABB::render(const GL::Pipeline& pipeline) const {
        AABB::render(*this, pipeline);
    }

    void AABB::updateBy(const glm::vec3& vertex) {
        if(getMin().x > vertex.x || !_initialized)
            setMinX(vertex.x);

        if(getMin().y > vertex.y || !_initialized)
            setMinY(vertex.y);

        if(getMin().z > vertex.z || !_initialized)
            setMinZ(vertex.z);

        if(getMax().x < vertex.x || !_initialized)
            setMaxX(vertex.x);

        if(getMax().y < vertex.y || !_initialized)
            setMaxY(vertex.y);

        if(getMax().z < vertex.z || !_initialized)
            setMaxZ(vertex.z);

        _initialized = true;
    }

    void AABB::setMin(const glm::vec3& min) {
        _min = min;
    }

    void AABB::setMax(const glm::vec3& max) {
        _max = max;
    }

    void AABB::setMin(float x, float y, float z) {
        setMin(glm::vec3(x, y, z));
    }

    void AABB::setMax(float x, float y, float z) {
        setMax(glm::vec3(x, y, z));
    }

    void AABB::setMinX(float x) {
        _min.x = x;
    }

    void AABB::setMinY(float y) {
        _min.y = y;
    }

    void AABB::setMinZ(float z) {
        _min.z = z;
    }

    void AABB::setMaxX(float x) {
        _max.x = x;
    }

    void AABB::setMaxY(float y) {
        _max.y = y;
    }

    void AABB::setMaxZ(float z) {
        _max.z = z;
    }

    const glm::vec3& AABB::getMin() const {
        return _min;
    }

    const glm::vec3& AABB::getMax() const {
        return _max;
    }

    glm::vec3 AABB::getCenter() const {
        return (_min + _max) * 0.5f;
    }

    bool AABB::intersect(const AABB& box1, const AABB& box2) {
        glm::bvec3 intersect(true);

        intersect.x = (box1.getMax().x > box2.getMin().x) && (box1.getMin().x < box2.getMax().x);
        intersect.y = (box1.getMax().y > box2.getMin().y) && (box2.getMin().y < box2.getMax().y);
        intersect.z = (box1.getMax().z > box2.getMin().z) && (box2.getMin().y < box2.getMax().y);
        
        return (intersect.x && intersect.y && intersect.z);
    }

    void AABB::render(const AABB& box, const GL::Pipeline& pipeline) {
        static GL::Program program;
        static GL::VertexArray vao;
        static GL::VertexBuffer vbo;
        static bool initialized = false;
        static std::vector<glm::vec3> vertices;

        AABB::setLines(box, vertices);

        if(initialized == false) {
            program.load(
                GL::Shader("assets/shaders/GLUL/AABB.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/AABB.fp", GL::Shader::Type::FragmentShader)
            );

            vbo.setUsage(GL::VertexBuffer::Usage::DynamicDraw);
            vao.bind();
                vbo.bind();
                    vao.enableAttrib(0);
                    vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                vbo.unbind();
            vao.unbind();

            vao.setDrawCount(vertices.size());
            vao.setDrawTarget(GL::VertexArray::DrawTarget::Lines);
        }

        pipeline.setModel();

        vbo.bind();
            vbo.setData(vertices);
        vbo.unbind();

        program.use();
        program["matrixMVP"].setMatrix(pipeline.getMVP());

            vao.bind();
            vao.drawArrays();
            vao.unbind();

        program.unbind();
    }

    std::vector<glm::vec3> AABB::getLines(const AABB& box) {
        std::vector<glm::vec3> result;

        AABB::setLines(box, result);

        return result;
    }

    void AABB::setLines(const AABB& box, std::vector<glm::vec3>& lines) {
        lines.clear();

        // Bottom horizontal lines
        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMin().z)); // 1
        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMin().z)); // 2
        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMax().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMax().z)); // 3
        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMax().z)); // 4
        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMax().z));

        // Top horizontal lines
        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMin().z)); // 5
        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMin().z)); // 6
        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMax().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMax().z)); // 7
        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMax().z)); // 8
        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMax().z));

        // Vertical lines
        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMin().z)); // 9
        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMin().z)); // 10
        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMin().z));

        lines.push_back(glm::vec3(box.getMax().x, box.getMin().y, box.getMax().z)); // 11
        lines.push_back(glm::vec3(box.getMax().x, box.getMax().y, box.getMax().z));

        lines.push_back(glm::vec3(box.getMin().x, box.getMin().y, box.getMax().z)); // 12
        lines.push_back(glm::vec3(box.getMin().x, box.getMax().y, box.getMax().z));
    }

}
