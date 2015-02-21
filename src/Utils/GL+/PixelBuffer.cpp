#include <Utils/GL+/PixelBuffer.h>

namespace GL {

    PixelBuffer::PixelBuffer() : Buffer(Target::PixelPack) {
        setPacking(Packing::Pack);
    }

    PixelBuffer::PixelBuffer(Packing packing, Usage usage) : Buffer(Target::PixelPack, usage) {
        setPacking(Packing::Pack);
    }

    PixelBuffer::PixelBuffer(PixelBuffer&& pbo) : Buffer(std::move(pbo)) {
        std::swap(_packing, pbo._packing);
    }

    PixelBuffer::~PixelBuffer() {

    }

    PixelBuffer& PixelBuffer::operator=(PixelBuffer&& pbo) {
        std::swap(_usage, pbo._usage);
        std::swap(_target, pbo._target);
        std::swap(_packing, pbo._packing);
        std::swap(_bufferID, pbo._bufferID);

        return *this;
    }

    void PixelBuffer::bind() const {
        Buffer::bind();
    }

    void PixelBuffer::bind(Packing packing) {
        setPacking(packing);
        bind();
    }

    void PixelBuffer::setTarget(Packing packing) {
        _packing = packing;

        if(packing == Packing::Pack)
            Buffer::setTarget(Target::PixelPack);
        else
            Buffer::setTarget(Target::PixelUnpack);
    }

    void PixelBuffer::setPacking(Packing packing) {
        setTarget(packing);
    }

    Buffer::Target PixelBuffer::getTarget() const {
        if(_packing == Packing::Pack)
            return Target::PixelPack;
        else
            return Target::PixelUnpack;
    }

    PixelBuffer::Packing PixelBuffer::getPacking() const {
        return _packing;
    }

}