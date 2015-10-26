/**
 * Project Pegaso
 */


#include "GestorCompetencias.h"

/**
 * GestorCompetencias implementation
 */


/**
 * @param datos
 * @return Competencia$
 */
Competencia$ GestorCompetencias::crearCompetencia(Datos datos) {
    return null;
}

/**
 * @param comp
 * @return bool
 */
bool GestorCompetencias::bajaCompetencia(Competencia$ comp) {
    return false;
}

/**
 * @param comp
 * @param datos
 * @return bool
 */
bool GestorCompetencias::modCompetencia(Competencia$ comp, Datos datos) {
    return false;
}

/**
 * @return QVector<Competencia>
 */
QVector<Competencia> GestorCompetencias::listarCompetencias() {
    return null;
}

/**
 * @param comp
 * @param datos
 * @return bool
 */
bool GestorCompetencias::altaParticipante(Competencia$ comp, Datos datos) {
    return false;
}

/**
 * @param comp
 * @param part
 * @return bool
 */
bool GestorCompetencias::eliminarParticipante(Competencia$ comp, Partido$ part) {
    return false;
}

/**
 * @param part
 * @param datos
 * @return bool
 */
bool GestorCompetencias::modParticipante(Participante$ part, Datos datos) {
    return false;
}

/**
 * @param comp
 * @param part
 * @param res
 */
void GestorCompetencias::nuevoResultado(Competencia$ comp, Partido$ part, Resultado$ res) {

}

/**
 * @param id_comp
 * @return Competencia$
 */
Competencia$ GestorCompetencias::getCompetenciaFull(int id_comp) {
    return null;
}

/**
 * @param id_usuario
 * @param filtros
 * @return QVector<Competencia>
 */
QVector<Competencia> GestorCompetencias::getCompetenciasLazy(int id_usuario, QVector<QString> filtros) {
    return null;
}

/**
 * @param comp
 * @return bool
 */
bool GestorCompetencias::generarFixture(Competencia$ comp) {
    return false;
}

/**
 * @param part
 * @param comp
 * @return bool
 */
bool GestorCompetencias::puedeModificar(Partido$ part, Competencia$ comp) {
    return false;
}