/* ----------------------------------------------------------------------------------------------- */
/*  Copyright (c) 2017 - 2019 by Axel Kenzo, axelkenzo@mail.ru                                     */
/*                                                                                                 */
/*  Файл ak_context_manager.h                                                                      */
/*  - содержит описание функций для управления контекстами.                                        */
/* ----------------------------------------------------------------------------------------------- */
#ifndef __AK_CONTEXT_MANAGER_H__
#define __AK_CONTEXT_MANAGER_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <ak_random.h>

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс состояний контекста. */
 typedef enum {
  /*! \brief контект не определен */
   node_undefined,
  /*! \brief контекст совпадает с хранимым вариантом (только создан/считан/записан) */
   node_is_equal,
  /*! \brief контекст изменен в процессе работы */
   node_modified
} context_node_status_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Элемент структуры, предназначенной для управления контекстами. */
 typedef struct context_node {
  /*! \brief указатель на контекст */
   ak_pointer ctx;
  /*! \brief дескриптор контекста */
   ak_handle handle;
  /*! \brief oid объекта */
   ak_oid oid;
  /*! \brief пользовательское описание */
   char *description;
  /*! \brief статус контекста */
   context_node_status_t status;
} *ak_context_node;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Создание нового элемента структуры управления контекстами. */
 ak_context_node ak_context_node_new( const ak_pointer , const ak_handle ,
                                                               const oid_engines_t , const char * );
/*! \brief Уничтожение элемента структуры управления контекстами. */
 ak_pointer ak_context_node_delete( ak_pointer );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура, предназначенная для управления контекстами.

    \details Менеджер контектов представляет собой массив контекстов (указателей на объекты),
    произвольных классов библиотеки, для которых
    механизмом OID определены стандартные действия (создание, удаление и т.п.).

    При инициализации библиотеки создается только один объект менеджера контекстов, который
    используется для работы с контекстами пользователей.
    Доступ пользователям библиотеки к менеджеру контекстов закрыт.                                 */
/* ----------------------------------------------------------------------------------------------- */
 typedef struct context_manager {
  /*! \brief массив указателей на структуры управления контекстами */
   ak_context_node *array;
  /*! \brief общее количество выделенной по структуры управления памяти */
   size_t size;
  /*! \brief генератор, используемый для выработки ключей */
   struct random key_generator;
} *ak_context_manager;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация структуры управления контекстами. */
 int ak_context_manager_create( ak_context_manager );
/*! \brief Уничтожение структуры управления контекстами. */
 int ak_context_manager_destroy( ak_context_manager );
/*! \brief Увеличение памяти для структуры управления контекстами. */
 int ak_context_manager_morealloc( ak_context_manager );
/*! \brief Добавление контекста в структуру управления контекстами. */
 ak_handle ak_context_manager_add_node( ak_context_manager ,
                                           const ak_pointer , const oid_engines_t , const char * );
/*! \brief Удаление контекста из структуры управления контекстами. */
 int ak_context_manager_delete_node( ak_context_manager , ak_handle );
/*! \brief Получение точного значения дескриптора по индексу массива. */
 ak_handle ak_context_manager_idx_to_handle( ak_context_manager , size_t );
/*! \brief Получение точного значения индекса массива по значению декскриптора. */
 size_t ak_context_manager_handle_to_idx( ak_context_manager , ak_handle );
/*! \brief Проверка корректности дескриптора контекста. */
 int ak_context_manager_handle_check( ak_context_manager , ak_handle , size_t * );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация глобальной структуры управления контекстами. */
 int ak_libakrypt_create_context_manager( void );
/*! \brief Удаление глобальной структуры управления контекстами. */
 int ak_libakrypt_destroy_context_manager( void );
/*! \brief Получение указателя на глобальную структуру управления контекстами. */
 ak_context_manager ak_libakrypt_get_context_manager( void );
/*! \brief Помещение созданного объекта в глобальную структуру управления контекстами. */
 ak_handle ak_libakrypt_add_context( ak_pointer , const oid_engines_t , const char * );
/*! \brief Получение контекста по заданному дескриптору и типу контекста. */
 ak_pointer ak_handle_get_context( ak_handle , oid_engines_t * );

#endif
/* ----------------------------------------------------------------------------------------------- */
/*                                                                           ak_context_manager.h  */
/* ----------------------------------------------------------------------------------------------- */
