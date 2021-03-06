/* ----------------------------------------------------------------------------------------------- */
/*  Copyright (c) 2014 - 2019 by Axel Kenzo, axelkenzo@mail.ru                                     */
/*                                                                                                 */
/*  Файл ak_random.h                                                                               */
/*  - содержит описания функций, реализующих генераторы псевдо-случайных чисел                     */
/* ----------------------------------------------------------------------------------------------- */
#ifndef    __AK_RANDOM_H__
#define    __AK_RANDOM_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <ak_oid.h>

/* ----------------------------------------------------------------------------------------------- */
 struct random;
/*! \brief Указатель на класс генератора псевдо-случайных чисел. */
 typedef struct random *ak_random;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция, принимающая в качестве аргумента указатель на структуту struct random. */
 typedef int ( ak_function_random )( ak_random );
/*! \brief Функция обработки данных заданного размера. */
 typedef int ( ak_function_random_ptr_const )( ak_random, const ak_pointer, const ssize_t );
/*! \brief Функция создания дескриптора генератора псевдо случайных чисел. */
 typedef ak_handle ( ak_function_random_new ) ( void );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Класс, реализующий произвольный генератор псевдо-случайных чисел.                       */
/* ----------------------------------------------------------------------------------------------- */
 struct random {
   /*! \brief указатель на внутренние структуры данных */
   ak_pointer data;
   /*! \brief OID генератора псевдо-случайных чисел. */
   ak_oid oid;
   /*! \brief указатель на функцию выработки следующего внутреннего состояния */
   ak_function_random *next;
   /*! \brief указатель на функцию инициализации генератора заданным массивом значений */
   ak_function_random_ptr_const *randomize_ptr;
   /*! \brief указатель на функцию выработки последователности псевдо-случайных байт */
   ak_function_random_ptr_const *random;
   /*! \brief указатель на функцию освобождения памяти внутренней структуры данных */
   ak_function_free *free;
 };

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация генератора псевдо-случайных чисел. */
 int ak_random_context_create( ak_random );
/*! \brief Уничтожение данных, хранящихся в полях структуры struct random. */
 int ak_random_context_destroy( ak_random );
/*! \brief Уничтожение генератора псевдо-случайных чисел. */
 ak_pointer ak_random_context_delete( ak_pointer );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Инициализация контекста линейного конгруэнтного генератора псевдо-случайных чисел. */
 int ak_random_context_create_lcg( ak_random );
/*! \brief Инициализация контекста генератора псевдо-случайных чисел xorshift64* (линейный регистр сдвига с нелинейным выходом). */
 int ak_random_context_create_xorshift32( ak_random );
 /*! \brief Инициализация контекста генератора, считывающего случайные значения из заданного файла. */
 int ak_random_context_create_file( ak_random , const char * );
#if defined(__unix__) || defined(__APPLE__)
/*! \brief Инициализация контекста генератора, считывающего случайные значения из /dev/random. */
 int ak_random_context_create_random( ak_random );
/*! \brief Инициализация контекста генератора, считывающего случайные значения из /dev/urandom. */
 int ak_random_context_create_urandom( ak_random );
#endif
#ifdef _WIN32
/*! \brief Инициализация контекста, реализующего интерфейс доступа к генератору псевдо-случайных чисел, предоставляемому ОС Windows. */
 int ak_random_context_create_winrtl( ak_random );
#endif
#ifdef LIBAKRYPT_CRYPTO_FUNCTIONS
/*! \brief Инициализация контекста генератора, основанного на применении функции хеширования Стрибог-256. */
 int ak_random_context_create_hashrnd_streebog256( ak_random );
/*! \brief Инициализация контекста генератора, основанного на применении функции хеширования Стрибог-512. */
 int ak_random_context_create_hashrnd_streebog512( ak_random );
/*! \brief Инициализация контекста генератора, основанного на применении функции хеширования, определяемой по ее идентификатору. */
 int ak_random_context_create_hashrnd_oid( ak_random , ak_oid );
#endif
#ifdef LIBAKRYPT_HAVE_SYSUN_H
/*! \brief Инициализация контекста генератора, считывающего случайные значения из сокета домена unix. */
 int ak_random_context_create_unix_domain_socket( ak_random , const char * , ssize_t );
#endif
/*! \brief Инициализация контекста генератора по заданному OID алгоритма генерации псевдо-случайных чисел. */
 int ak_random_context_create_oid( ak_random, ak_oid );
/*! \brief Установка внутреннего состояния генератора псевдо-случайных чисел. */
 int ak_random_context_randomize( ak_random , const ak_pointer , const ssize_t );
/*! \brief Выработка псевдо-случайных данных. */
 int ak_random_context_random( ak_random , const ak_pointer , const ssize_t );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Неэкспортируемая функция генерации случайного 64-х битного целого числа. */
 ak_uint64 ak_random_value( void );

#endif
/* ----------------------------------------------------------------------------------------------- */
/*                                                                                    ak_random.h  */
/* ----------------------------------------------------------------------------------------------- */
