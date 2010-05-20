#ifndef _MEMPAGE_H_
#define _MEMPAGE_H_

/**
 * @file memory.h
 */

#include <types.h>

#define PAGE_SIZE 4096
#define BIOS_RESERVED_BASE 0xa0000
#define BIOS_RESERVED_TOP 0x100000

/**
 * @struct physical_page_descr
 * @brief Descripteur de page physique.
 *
 * Descripteur de page physique. Contient juste l'adresse physique de la zone 
 * mémoire et des pointeurs vers les pages suivantes et précédentes.
 */
struct physical_page_descr {
	paddr_t addr; /**< L'adresse physique de la zone mémoire. */

	/* Cet élément fera parti d'un liste doublement chainée (page utilisée ou libre) */
	struct physical_page_descr *next; /**< Pointeur sur le descripteur suivant. */
	struct physical_page_descr *prev; /**< Pointeur sur le descripteur précédent. */
};

/** 
 * @brief Affiche la mémoire physique.
 *
 * Affiche la mémoire physique à l'aide de caractères F (libre) ou 
 * U (utilisée) pour chaque cadre de page.
 */
void memory_print();

/** 
 * @brief Affiche la liste des cadres utilisés.
 *
 * Affiche la liste des cadres utilisés en donnant simplement la liste des adresses.
 */
void memory_print_used_pages();

/** 
 * @brief Affiche la liste des cadres libres.
 *
 * Affiche la liste des cadres libres en donnant simplement la liste des adresses.
 */
void memory_print_free_pages();

/**
 * @brief Découpage de la mémoire physique en cadres de page.
 *
 * Découpage de la mémoire physique en taille fixe. Pour l'instant il n'y a 
 * pas de mémoire virtuelle, c'est donc juste une association linéaire avec 
 * autant de pages que de cadres.
 *
 * ram_size taille de la mémoire physique en octets.
 */
void memory_setup(size_t ram_size);

/** 
 * @brief Réserve un cadre de page.
 *
 * Réserve un cadre de page libre, le place dans la liste des cadres utilisés
 * et retourne l'adresse physique du cadre.
 * 
 * @return l'adresse physique du cadre réservé. 0 en cas d'erreur.
 */
paddr_t memory_reserve_page_frame();

/** 
 * @brief Libère un cadre de page.
 *
 * Libère un cadre de page occupé, le place dans la listes des cadres libres
 * et retourne 0 en cas de succès.
 * 
 * @param addr l'adresse physique du cadre à libérer.
 * 
 * @return 0 en cas de succès. Une autre valeur sinon.
 */
int memory_free_page_frame(paddr_t addr);

/** 
 * @brief Donne une copie du pointeur du premier descripteur de cadre de page 
 *			 utilisés.
 *
 * Donne une copie du pointeur du haut de la pile des descripteurs de cadre de 
 * page utilisés.
 *
 * @return pointeur sur le premier descripteur de cadre de page utilisé.
 */
struct physical_page_descr * memory_get_first_used_page();

/** 
 * @brief Donne une copie du pointeur du premier descripteur de cadre de page 
 *			 libres.
 *
 * Donne une copie du pointeur du haut de la pile des descripteurs de cadre de 
 * page libres.
 *
 * @return pointeur sur le premier descripteur de cadre de page libre.
 */
struct physical_page_descr * memory_get_first_free_page();
 
 /** 
  * @brief Retourne vrai s'il y a encore un cadre de page qui suit.
  * 
  * Retourne vrai s'il y a encore un cadre de page qui suit.
  *
  * @param iterator pointeur de descripteur de page.
  * 
  * @return vrai s'il y a encore un cadre de page qui suit.
  */
bool memory_has_next_page(struct physical_page_descr * iterator);

/** 
 * @brief Retourne le prochain cadre de page.
 * 
 * Cette fonction sert à autoriser une itération sur les listes de cadres de 
 * page sans manipuler directement les pointeurs next et prev.
 *
 * @param iterator adresse d'un pointeur de descripteur de page. 
 * Sera modifiée pour pointer sur l'élément suivant.
 * 
 * @return l'adresse physique du cadre de page.
 */
paddr_t memory_next_page(struct physical_page_descr ** iterator);

#endif
