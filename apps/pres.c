#include <stdio.h>
#include <gui.h>
#include <process.h>

#define NB_SLIDES 13

int current = 0;
struct widget_t* title[NB_SLIDES];
struct widget_t* txt[NB_SLIDES];

void intro(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\n"
"\n"
"\n"
"\n"
"           \033[32m    +---------------------------------------------+  \033[30m\n"
"           \033[32m    |\033[30m R�alisation d'un syst�me d'exploitation x86 \033[32m|  \033[30m\n"
"           \033[32m    +---------------------------------------------+  \033[30m\n"
"\n"
"\n"
"\n"
"\n"
"\n"
" Maxime Cheramy\n"
" Nicolas Floquet\n"
" Benjamin Hautbois                                              9 juin 2010\n"
" Ludovic Rigal                                4�me Ann�e G�nie Informatique\n"
" Simon Vernhes                                                INSA Toulouse\n");
	*title = addButton(win,"Pr�sentation de projet tutor�");
}

void plan(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[31m      I) M�moire\n"
"\033[34m         a. Pagination\n"
"\033[34m         b. Allocation m�moire\n"
"\033[31m      II) Interruptions\n"
"\033[34m         a. IDT \n"
"\033[34m         b. Wrapper\n"
"\033[34m         c. Gestion du temps\n"
"\033[31m      III) Gestion des processus\n"
"\033[34m         a. Changement de contexte\n"
"\033[34m         b. Appels syst�me\n"
"\033[34m         c. Ordonnancement\n"
"\033[31m      IV) Pilotes\n"
"\033[34m         a. Clavier/Souris\n"
"\033[34m         b. Disquette\n"
"\033[31m      V) Entr�es/sorties\n"
"\033[34m         a. Syst�me de fichier FAT\n"
"\033[34m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}
void plan1(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[32m      I) M�moire\n"
"\033[32m         a. Pagination\n"
"\033[32m         b. Allocation m�moire\n"
"\033[30m      II) Interruptions\n"
"\033[30m         a. IDT \n"
"\033[30m         b. Wrapper\n"
"\033[30m         c. Gestion du temps\n"
"\033[30m      III) Gestion des processus\n"
"\033[30m         a. Changement de contexte\n"
"\033[30m         b. Appels syst�me\n"
"\033[30m         c. Ordonnancement\n"
"\033[30m      IV) Pilotes\n"
"\033[30m         a. Clavier/Souris\n"
"\033[30m         b. Disquette\n"
"\033[30m      V) Entr�es/sorties\n"
"\033[30m         a. Syst�me de fichier FAT\n"
"\033[30m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}
void plan2(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[30m      I) M�moire\n"
"\033[30m         a. Pagination\n"
"\033[30m         b. Allocation m�moire\n"
"\033[32m      II) Interruptions\n"
"\033[32m         a. IDT \n"
"\033[32m         b. Wrapper\n"
"\033[32m         c. Gestion du temps\n"
"\033[30m      III) Gestion des processus\n"
"\033[30m         a. Changement de contexte\n"
"\033[30m         b. Appels syst�me\n"
"\033[30m         c. Ordonnancement\n"
"\033[30m      IV) Pilotes\n"
"\033[30m         a. Clavier/Souris\n"
"\033[30m         b. Disquette\n"
"\033[30m      V) Entr�es/sorties\n"
"\033[30m         a. Syst�me de fichier FAT\n"
"\033[30m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}
void plan3(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[30m      I) M�moire\n"
"\033[30m         a. Pagination\n"
"\033[30m         b. Allocation m�moire\n"
"\033[30m      II) Interruptions\n"
"\033[30m         a. IDT \n"
"\033[30m         b. Wrapper\n"
"\033[30m         c. Gestion du temps\n"
"\033[32m      III) Gestion des processus\n"
"\033[32m         a. Changement de contexte\n"
"\033[32m         b. Appels syst�me\n"
"\033[32m         c. Ordonnancement\n"
"\033[30m      IV) Pilotes\n"
"\033[30m         a. Clavier/Souris\n"
"\033[30m         b. Disquette\n"
"\033[30m      V) Entr�es/sorties\n"
"\033[30m         a. Syst�me de fichier FAT\n"
"\033[30m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}
void plan4(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[30m      I) M�moire\n"
"\033[30m         a. Pagination\n"
"\033[30m         b. Allocation m�moire\n"
"\033[30m      II) Interruptions\n"
"\033[30m         a. IDT \n"
"\033[30m         b. Wrapper\n"
"\033[30m         c. Gestion du temps\n"
"\033[30m      III) Gestion des processus\n"
"\033[30m         a. Changement de contexte\n"
"\033[30m         b. Appels syst�me\n"
"\033[30m         c. Ordonnancement\n"
"\033[32m      IV) Pilotes\n"
"\033[32m         a. Clavier/Souris\n"
"\033[32m         b. Disquette\n"
"\033[30m      V) Entr�es/sorties\n"
"\033[30m         a. Syst�me de fichier FAT\n"
"\033[30m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}
void plan5(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"\033[30m      I) M�moire\n"
"\033[30m         a. Pagination\n"
"\033[30m         b. Allocation m�moire\n"
"\033[30m      II) Interruptions\n"
"\033[30m         a. IDT \n"
"\033[30m         b. Wrapper\n"
"\033[30m         c. Gestion du temps\n"
"\033[30m      III) Gestion des processus\n"
"\033[30m         a. Changement de contexte\n"
"\033[30m         b. Appels syst�me\n"
"\033[30m         c. Ordonnancement\n"
"\033[30m      IV) Pilotes\n"
"\033[30m         a. Clavier/Souris\n"
"\033[30m         b. Disquette\n"
"\033[32m      V) Entr�es/sorties\n"
"\033[32m         a. Syst�me de fichier FAT\n"
"\033[32m         b. Stdin/Stdout\n");
	*title = addButton(win,"Sommaire");
}

void schema_vmm(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, "                    ^                                   ^\n"
"                    |                                   |\n"
"  Fin de la zone    |                                   |\n"
"  g�r�e par     --->|-----------------------------------| -\n"
"  vmm.c (vmm_top)   |\033[43m         (zone utilis�e)           \033[47m| | Bloc de\n"
"                    |\033[44m\033[34m-----------------------------------\033[47m\033[030m| | 2 pages\n"
"                    |-----------------------------------| -\n"
"                    | Zone pages virtuelles non mapp�es | | \n"
"                    |      � des pages physiques.       | | Bloc de\n"
"                    |           (zone libre)            | | 4 pages\n"
"                    |\033[44m\033[34m-----------------------------------\033[47m\033[030m| |\n"
"                    |-----------------------------------| -\n"
"                    |\033[43mZone pages virtuelles mapp�es � des\033[47m| | Bloc de    \n"
"                    |\033[43m pages physiques. (zone utilis�e)  \033[47m| | 3 pages \n"
"                    |-----------------------------------| | (= 12 kio)\n"
"    D�but de la     |\033[44m\033[37mStructure d�crivant le bloc (16 o) \033[47m\033[030m| |\n"
"    zone g�r�e  --->|-----------------------------------| -\n"
"    par vmm.c       |       Noyau - Identity Mapped     |\n"
"                    |___________________________________|\n");
	*title = addButton(win,"VMM");
}

void schema_pagination(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, "Adresse : \033[32m########## \033[31m########## \033[34m############\033[0m\n"
"          <--------> <--------> <---------->\n"
"            |             |________    |_______________\n"
"            |            Indice de |        Offset dans|\n"
"            |             la page  |         la page   |\n"
"      Indice|    ________          |    ________       |    ________ \n"
"      de la |   |        |         |   |        |      |   |        |\n"
"      table |   |________|         |   |________|      |   |        |\n"
"            |   | @ phys |         |   | @ phys |      |   |        |\n"
"            |-->|  table |--|      |-->|  page  |---|  |-->|________|\n"
"                |________|  |          |________|   |      |        |\n"
"                |        |  |          |        |   |      |        |\n"
"                |........|  |          |........|   |      |........|\n"
"                |        |  |          |        |   |      |        |\n"
"          CR3-->|________|  |--------->|________|   |----->|________|\n"
"               Repertoire de         Table de pages       Page (4 kio)\n"
"              tables de pages        (1024 entrees)\n");
	*title = addButton(win,"Pagination");
}

void schema_ordonnanceur(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"\n"
"      \033[30m               \033[30m                                    \033[30mEBP___\033[30m  \n"
"    pi\033[30mle kernel -----\033[30m->                                  \033[30m      \033[30m|  \n"
"  ____\033[32m __ __ __ __ __\033[34m __ __ __ __ __ __ __ __ __ __ __ __\033[31m __ __\033[30mV__\n"
"      \033[32m|  |  |  |  |  \033[34m|  |  |  |  |k |  |  |  |  |  |  |  \033[31m|k |k \033[30m|  \n"
"      \033[32m|s |e |e |c |e \033[34m|e |e |e |e |e |e |e |e |d |e |f |g \033[31m|e |e \033[30m|  \n" 
"    ..\033[32m|s |s |f |s |i \033[34m|a |c |d |b |s |b |s |d |s |s |s |s \033[31m|i |b \033[30m|..\n"
"      \033[32m|  |p |l |  |p \033[34m|x |x |x |x |p |p |i |i |  |  |  |  \033[31m|p |p \033[30m|  \n"
"  ____\033[32m|__|__|__|__|__\033[34m|__|__|__|__|__|__|__|__|__|__|__|__\033[31m|__|__\033[30m|__\n"
"      \033[30m |           | \033[30m |                                 |\033[30m |   |\033[30m   \n"
"      \033[30m |___________| \033[30m |_________________________________|\033[30m |___|\033[30m   \n"
"      \033[30m       |       \033[30m                 |                  \033[30m   |             \n"
"      \033[32mempil� par le  \033[34m    empil� apr�s l'interruption     \033[31m empil� �        \n"
"      \033[32mm�canisme d'   \033[34m                                    \033[31m l'appel de      \n"
"      \033[32minterruption   \033[34m                                    \033[31m l'ordonnanceur\033[30m\n");
	*title = addButton(win,"Ordonnanceur");
}


void slide_disquette(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win,
"                               \033[31mRegistres\033[30m\n"
"\n"
"\033[34mData FIFO\033[30m: envoi des commandes au controleur\n"
"\033[34mMain status register\033[30m: informations sur le status du controleur\n"
"\033[34mDigital output register\033[30m: controle du moteur, activation du DMA et de l'IRQ\n"
"\033[34mConfiguration control register\033[30m: sp�cification du d�bit de transfert\n"
"\n"
"                               \033[31mCommandes\033[30m\n"
"\n"
"\033[32mSpecify\033[30m         : donne au controleur des informations sur le lecteur\n"
"\033[32mWrite/Read data\033[30m : �crit/Lit un ou plusieurs secteurs sur la disquette\n"
"\033[32mRecalibrate\033[30m     : positionne les tetes en but�e sur le cylindre 0\n"
"\033[32mSense interrupt\033[30m : r�cup�re des informations sur une interruption\n"
"\033[32mSeek\033[30m            : d�place la tete de lecture/�criture � un cylindre donn�\n"
"\033[32mVersion\033[30m         : d�termine la version du controleur\n");
	*title = addButton(win,"Driver disquette");
}



void schema_fat(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"                       Partition FAT       \n"
"                \033[34m ________________________ \033[30m \n"
"                \033[34m|      Secteur de boot   |\033[30m<---*\n"
"                \033[34m|________________________|\033[30m    |\n"
"                \033[34m| File Allocation Tables |\033[30m    |\n"
"                \033[34m|________________________|\033[30m    |-- \033[34mZone r�serv�e\n"
"                \033[34m|                        |\033[30m    |\n"
"                \033[34m|    R�pertoire Racine   |\033[30m    |\n"
"                \033[34m|________________________|\033[30m<---*\n"
"                \033[32m|                        |\033[30m<---*\n"
"                \033[32m|                        |\033[30m    |\n"
"                \033[32m|       Fichiers et      |\033[30m    |\n"
"                \033[32m|    sous r�pertoires    |\033[30m    |\n"
"                \033[32m|                        |\033[30m    |-- \033[32mZone des donn�es\n" 
"                \033[32m|                        |\033[30m    |\n"
"                \033[32m|                        |\033[30m    |\n"
"                \033[32m|                        |\033[30m    |\n"
"                \033[32m|________________________|\033[30m<---*\n");
	*title = addButton(win,"Syst�me de fichiers FAT");
}

void diapo_fat(struct window_t *win, struct widget_t** txt, struct widget_t** title) {
	*txt = addTxt(win, 
"                     \033[31mInterpr�tation des valeurs de la FAT\033[30m\n"
"\n"
"\n"
"          \033[32m0x000\033[30m          Cluster vide\n"
"          \033[32m0x001\033[30m          Cluster r�serv�\n"
"          \033[32m0x002 - 0xFEF\033[30m  Pointeur vers le cluster suivant du fichier\n"
"          \033[32m0xFF0 - 0xFF6\033[30m  Valeurs r�serv�es\n"
"          \033[32m0xFF7\033[30m          Cluster d�fectueux\n"
"          \033[32m0xFF8 - 0xFFF\033[30m  Dernier cluster d'un fichier\n"
"\n"
"\n"
"                        \033[31mEntr�e r�pertoire - 32 octets\033[30m\n"
"\n"
"                          Nom | Extension | \033[34mAttributs\033[30m\n"
"                   Date/Heure cr�ation | Date dernier acc�s\n"
"                       Date/Heure derni�res modifications\n"
"                    \033[34mNo du premier cluster\033[30m | \033[34mTaille en octet\033[30m\n");

	*title = addButton(win,"Syst�me de fichiers FAT");
}

void goBack(struct widget_t* wdg, int x, int y)
{
  if(current <= 0)
    return;

	setVisible(title[current],0);
	setVisible(txt[current],0);

  current = (current-1);

	setVisible(title[current],1);
	setVisible(txt[current],1);
}

void goForward(struct widget_t* wdg, int x, int y)
{
  if(current >= NB_SLIDES-1)
    return;

  setVisible(title[current],0);
	setVisible(txt[current],0);

	current = (current+1);

	setVisible(title[current],1);
	setVisible(txt[current],1);
}

int main_pres(int argc __attribute__ ((unused)), char* argv[] __attribute__ ((unused)))
{
	struct window_t* win;
	struct widget_t* bck;
	struct widget_t* nxt;

	int i;
		
	win = createWindow(0, 7);

	i=0;
	intro(win,&txt[i],&title[i]);
	i++;
	plan(win,&txt[i],&title[i]);
	i++;
	plan1(win,&txt[i],&title[i]);
	i++;
	schema_pagination(win,&txt[i],&title[i]);
	i++;
	schema_vmm(win,&txt[i],&title[i]);
	i++;
	plan2(win,&txt[i],&title[i]);
	i++;
	plan3(win,&txt[i],&title[i]);
	i++;
	schema_ordonnanceur(win,&txt[i],&title[i]);
	i++;
	plan4(win,&txt[i],&title[i]);
	i++;
	slide_disquette(win,&txt[i],&title[i]);
	i++;
	plan5(win,&txt[i],&title[i]);
	i++;
	schema_fat(win,&txt[i],&title[i]);
	i++;
	diapo_fat(win,&txt[i],&title[i]);

	for(i=0 ; i<NB_SLIDES ; i++)
	{
		setVisible(txt[i],0);
		setVisible(title[i],0);
		setWidgetProperties(txt[i], 1 , 4, 20, 78, 7, 0);
		setWidgetProperties(title[i], 7, 1, 3, 66, 7, 0);
	}

	setVisible(title[current],1);
	setVisible(txt[current],1);

	bck = addButton(win,"Prec");
	setWidgetProperties(bck,  1 , 1, 3, 6, 5, 0);
	setOnClick(bck,goBack);
	nxt = addButton(win,"Suiv");
	setWidgetProperties(nxt, 73, 1, 3, 6, 5, 0);
	setOnClick(nxt,goForward);

	runWindow(win);
	
	return 0;
}

int launch_pres()
{
	exec(main_pres, "presentation");
	return 0;
}

