//
//	DTO's
//

// DTO para getCompetencia

class DtoCompetencia
{
public:
	QString user;
	QVector<QString> filtros[4];
	DtoCompetencia(QString u , QVector<QString> filtros = {NULL,NULL,NULL,NULL} );
	
};

DtoCompetencia::DtoCompetencia(QString u , QVector<QString> filtros){
	
	user = u;
	filtros[0] = nombreCom;
	filtros[1] = deporte;
	filtros[2] = modalidad;
	filtros[3] = estado;

}

