#include "tablero.h"

void				/* Esta función busca a los reyes en la estructura tablero y necesita direcciones de memoria a las que les asignara un valor para que desde donde se haya llamado, se puedan trabajar */
buscar_reyes (int *columna_K, int *fila_K, int *columna_k, int *fila_k,
	      struct tablero *un_tablero)
{
  int i = 0;
  int j = 0;
  while (i < 8)
    {
      while (j < 8)
	{
	  if (un_tablero->casillas[i][j] == 'K')
	    {
	      *(columna_K) = j;
	      *(fila_K) = i;
	    }
	  if (un_tablero->casillas[i][j] == 'k')
	    {
	      *(columna_k) = j;
	      *(fila_k) = i;
	    }
	  j = j + 1;
	}
      j = 0;
      i = i + 1;
    }
  return;
}

int				/*Busca si hay alguna pieza negra que amenaze al rey blanco y si es valido regresa 1 si no hay ninguna pieza que lo amenaze regresa 0 */
buscar_atacantes_negros (int fila_K, int columna_K,
			 struct tablero *un_tablero)
{
  int i = 0;
  int j = 0;
  int valor_de_jaque = 0;
  while (i < 8)
    {
      while (j < 8)
	{
	  switch (un_tablero->casillas[i][j])
	    {
	    case 'p':
	      valor_de_jaque =
		validar_movimiento_peon (un_tablero, j, i, fila_K, columna_K);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'c':
	      valor_de_jaque =
		validar_movimiento_caballo (un_tablero, j, i, fila_K,
					    columna_K);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 't':
	      valor_de_jaque =
		validar_movimiento_torre (un_tablero, j, i, fila_K,
					  columna_K);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'a':
	      valor_de_jaque =
		validar_movimiento_alfil (un_tablero, j, i, fila_K,
					  columna_K);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'q':
	      valor_de_jaque =
		validar_movimiento_reina (un_tablero, j, i, fila_K,
					  columna_K);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    default:
	      break;
	    }
	  j = j + 1;
	}
      j = 0;
      i = i + 1;
    }
  return 0;
}

int				/*Busca si hay alguna pieza blanca que amenaze al rey negro y si es valido regresa 1 si no hay ninguna pieza que lo amenaze regresa 0 */
buscar_atacantes_blancos (int fila_k, int columna_k,
			  struct tablero *un_tablero)
{
  int i = 0;
  int valor_de_jaque = 0;
  int j = 0;
  while (i < 8)
    {
      while (j < 8)
	{

	  switch (un_tablero->casillas[i][j])
	    {
	    case 'P':
	      valor_de_jaque =
		validar_movimiento_peon (un_tablero, j, i, fila_k, columna_k);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'C':
	      valor_de_jaque =
		validar_movimiento_caballo (un_tablero, j, i, fila_k,
					    columna_k);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'T':
	      valor_de_jaque =
		validar_movimiento_torre (un_tablero, j, i, fila_k,
					  columna_k);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'A':
	      valor_de_jaque =
		validar_movimiento_alfil (un_tablero, j, i, fila_k,
					  columna_k);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    case 'Q':
	      valor_de_jaque =
		validar_movimiento_reina (un_tablero, j, i, fila_k,
					  columna_k);
	      if (valor_de_jaque == 1)
		{
		  return 1;
		}
	      break;
	    default:
	      break;

	    }
	  j = j + 1;
	}
      j = 0;
      i = i + 1;
    }
  return 0;
}

int				/*Verifica si existe jaque para blancos o negros , regresa 0 si ninguna esta en jaque, 1 para blancos, 2 para negros */
verificar_jaque (struct tablero *un_tablero)
{
  int columna_k = 0;
  int fila_k = 0;
  int columna_K = 0;
  int fila_K = 0;
  int valor_de_jaque1 = 0;
  int valor_de_jaque2 = 0;
  buscar_reyes (&(columna_K), &(fila_K), &(columna_k), &(fila_k), un_tablero);
  valor_de_jaque1 = buscar_atacantes_negros (fila_K, columna_K, un_tablero);
  valor_de_jaque2 = buscar_atacantes_blancos (fila_k, columna_k, un_tablero);
  if (valor_de_jaque1 == 1)
    {
      return 1;
    }
  if (valor_de_jaque2 == 1)
    {
      return 2;
    }
  return 0;
}

int				/*Verifica si existe jaque_mate para blancos o negros , regresa 0 si ninguna esta en jaque, 1 para blancos, 2 para negros */
verificar_jaque_mate (struct tablero *un_tablero)
{
  int i = 0;
  int columna_K = 0;
  int fila_K = 0;
  int columna_k = 0;
  int fila_k = 0;
  int estado_blancas = 0;
  int estado_negras = 0;
  int direccion[8][2] =
    { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

  buscar_reyes (&(columna_K), &(fila_K), &(columna_k), &(fila_k), un_tablero);

  estado_blancas = verificar_jaque (un_tablero);
  estado_negras = verificar_jaque (un_tablero);

  if (estado_blancas == 1)
    while (i < 8)
      {
	estado_blancas =
	  estado_blancas +
	  (validar_movimiento_rey
	   (un_tablero, columna_K, fila_K, (columna_K + direccion[i][1]),
	    (fila_K + direccion[i][0])));
	if (estado_blancas == -7)
	  {
	    return 1;
	  }
	i = i + 1;
      }
  i = 0;
  if (estado_negras == 1)
    {

      while (i < 8)
	{
	  estado_negras =
	    estado_negras +
	    (validar_movimiento_rey
	     (un_tablero, fila_k, columna_k, (fila_k + direccion[i][0]),
	      (columna_k + direccion[i][1])));
	  if (estado_negras == -7)
	    {
	      return 2;
	    }
	  i = i + 1;
	}
    }
  return 0;
}

int
paso (struct tablero *un_tablero, int columna, int fila)	/* Esta función recibe las coordenadas de posición y regresa 1 si en ese posición hay una casilla blanca o negra (está vacío) y 0 si no */
{
  if (un_tablero->casillas[fila][columna] == 'X' || un_tablero->casillas[fila][columna] == ' ')	/*Reescribí la condición con un || */
    {				/*Si no se puede usar simplemente regresarlo al código anterior */
      return 1;
    }
  return 0;
}

int
conocer_turno_jugador (int turno, struct tablero *un_tablero)	/*Esta función podria complementar la funcion girar tablero */
{
  int mueve = 0;
  if ((turno % 2) == 0)
    {
      mueve = 0;
      printf ("\nMueven blancas");
      invertir_tablero (un_tablero);	/*Aquí se requiere la función invertir tablero */
      return mueve;

    }
  if ((turno % 2) == 1)
    {
      printf ("\nMueven negras");
      mueve = 1;
      invertir_tablero (un_tablero);	/*Aquí se requiere la función invertir tablero */
      return mueve;
    }
  return 0;
}

void
invertir_tablero (struct tablero *un_tablero)	/*Esta función invierte el tablero como si se girara 180° grados */
{
  char tempo[8][8];
  int i = 0;
  int j = 0;
  int c_i = 7;
  int f_i = 7;
  while (i < 8)
    {
      while (j < 8)
	{
	  tempo[i][j] = un_tablero->casillas[i][j];
	  j = j + 1;
	}
      i = i + 1;
      j = 0;
    }
  i = 0;
  j = 0;
  while (f_i >= 0)
    {
      while (c_i >= 0)
	{
	  un_tablero->casillas[i][j] = tempo[f_i][c_i];
	  j = j + 1;
	  c_i = c_i - 1;
	}
      c_i = 7;
      j = 0;
      i = i + 1;
      f_i = f_i - 1;
    }
}

int
obtener_posicion (int Columna, int Fila)	/* Esta función transforma la columna y la fila a un valor de 1 a 64, columna y fila tienen valor del 0 al 7(por ser de un arreglo de 8x8) */
{
  int i = 0;
  int cuadrante = 0;
  Fila = Fila + 1;
  while (Columna != 0 + i)
    {
      i = i + 1;
    }
  cuadrante = (8 * (Fila - 1)) + (i + 1);
  return cuadrante;
}

char
color_remplazo (int columna, int fila)	/* Esta función regresa un caracter del color sobre el cual la pieza se encontraba antes de desplazarse */
{
  int alterno = 0;
  int cuadrante = 0;
  int j = 1;
  char color = 'X';
  cuadrante = obtener_posicion (columna, fila);
  while (j <= 64)
    {
      if (cuadrante == j)
	{
	  return color;
	}
      if (alterno != 8)
	{
	  switch (color)
	    {
	    case 'X':
	      color = ' ';
	      break;
	    case ' ':
	      color = 'X';
	      break;
	    }
	}
      if (alterno == 8)
	{
	  alterno = 0;
	}
      alterno = alterno + 1;
      j = j + 1;
    }
  return color;
}

void
iniciar_tablero (struct tablero *un_tablero)
{
  int columna = 0;
  int fila = 0;
  int i = 0;
  int j = 0;
  char VACIA = 'X';
  int alterno = 0;

  /* piezas blancas sin contar al peón */
  un_tablero->casillas[7][0] = 'T';
  un_tablero->casillas[7][1] = 'C';
  un_tablero->casillas[7][2] = 'A';
  un_tablero->casillas[7][3] = 'Q';
  un_tablero->casillas[7][4] = 'K';
  un_tablero->casillas[7][5] = 'A';
  un_tablero->casillas[7][6] = 'C';
  un_tablero->casillas[7][7] = 'T';

  /* piezas negras sin contar al peón */
  un_tablero->casillas[0][0] = 't';
  un_tablero->casillas[0][1] = 'c';
  un_tablero->casillas[0][2] = 'a';
  un_tablero->casillas[0][3] = 'q';
  un_tablero->casillas[0][4] = 'k';
  un_tablero->casillas[0][5] = 'a';
  un_tablero->casillas[0][6] = 'c';
  un_tablero->casillas[0][7] = 't';

  /* Inicialización de peones, de acuerdo al orden asignado, negras se ven arriba y blancas abajo (últimas filas). */
  while (i < 8)
    {
      un_tablero->casillas[6][i] = 'P';
      un_tablero->casillas[1][i] = 'p';
      i = i + 1;
    }
  i = 2;
  /* espacios vacios */
  while (i < 6)
    {
      while (j < 8)
	{
	  un_tablero->casillas[i][j] = VACIA;
	  j = j + 1;
	  if (alterno != 8)
	    {
	      switch (VACIA)
		{
		case 'X':
		  VACIA = ' ';
		  break;
		case ' ':
		  VACIA = 'X';
		  break;
		}
	    }
	  if (alterno == 8)
	    {
	      alterno = 0;
	    }
	  alterno = alterno + 1;
	}
      j = 0;
      i = i + 1;
    }

  /* movimiento: 0 no se movió, 1 si se movió */
  for (fila = 0; fila < 8; fila++)
    {
      for (columna = 0; columna < 8; columna++)
	{
	  un_tablero->se_movio[columna][fila] = 0;
	}
    }
}

/*

#define Negro    "\x1b[30m"
#define RESET   "\x1b[0m"
int
tablero_negro (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Rojo    "\x1b[31m"
#define RESET   "\x1b[0m"
int
tablero_rojo (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Verde    "\x1b[32m"
#define RESET   "\x1b[0m"
int
tablero_verde (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Amarillo    "\x1b[33m"
#define RESET   "\x1b[0m"
int
tablero_amarillo (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Azul    "\x1b[34m"
#define RESET   "\x1b[0m"
int
tablero_azul (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Magenta    "\x1b[35m"
#define RESET   "\x1b[0m"
int
tablero_magenta (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}

#define Cyan    "\x1b[36m"
#define RESET   "\x1b[0m"
int
tablero_cyan (void)
{
  char tablero[8][8];
  int i = 0;
  int j = 0;
  int e = 0;
}*/
