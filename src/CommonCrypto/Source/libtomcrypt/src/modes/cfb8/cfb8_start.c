/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */
#include "tomcrypt.h"

/**
   @file cfb8_start.c
   CFB implementation, start chain, Tom St Denis
*/


#ifdef LTC_CFB_MODE

/**
   Initialize a CFB8 context
   @param cipher      The index of the cipher desired
   @param IV          The initial vector
   @param key         The secret key 
   @param keylen      The length of the secret key (octets)
   @param num_rounds  Number of rounds in the cipher desired (0 for default)
   @param cfb         The CFB state to initialize
   @return CRYPT_OK if successful
*/
#ifdef MACTOMCRYPT
int cfb8_start(int cipher, const unsigned char *IV, const unsigned char *key, int keylen, const unsigned char *tweak, int tweaklen,
	int num_rounds, int options, symmetric_CFB *cfb)
#else
int cfb8_start(int cipher, const unsigned char *IV, const unsigned char *key, 
              int keylen, int num_rounds, symmetric_CFB *cfb)
#endif
{
   int x, err;

   LTC_ARGCHK(IV != NULL);
   LTC_ARGCHK(key != NULL);
   LTC_ARGCHK(cfb != NULL);

   if ((err = cipher_is_valid(cipher)) != CRYPT_OK) {
      return err;
   }
   

   /* copy data */
   cfb->cipher = cipher;
   cfb->blocklen = cipher_descriptor[cipher].block_length;
   for (x = 0; x < cfb->blocklen; x++)
       cfb->IV[x] = IV[x];

   /* init the cipher */
   if ((err = cipher_descriptor[cipher].setup(key, keylen, num_rounds, &cfb->key)) != CRYPT_OK) {
      return err;
   }

   /* encrypt the IV */
   return cipher_descriptor[cfb->cipher].ecb_encrypt(cfb->IV, cfb->pad, &cfb->key);
}

#endif

/* $Source: /cvs/libtom/libtomcrypt/src/modes/cfb/cfb_start.c,v $ */
/* $Revision: 1.7 $ */
/* $Date: 2006/12/28 01:27:24 $ */
