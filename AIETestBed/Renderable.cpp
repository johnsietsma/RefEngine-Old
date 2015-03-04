#include "Renderable.h"

Renderable::Renderable(ProgramId programId, std::shared_ptr<Material> material , std::shared_ptr<Buffer> buffer)
: m_programId(programId)
, m_material(material)
, m_buffer(buffer)
{}
