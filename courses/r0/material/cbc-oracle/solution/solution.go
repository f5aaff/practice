package main

import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"encoding/hex"
	"fmt"
	"os"
)

const (
	ENCRYPT = 0
	DECRYPT = 1
)

func main() {
	if len(os.Args) != 4 {
		fmt.Println("usage: ", os.Args[0], "e|d <iv> <plaintext|ciphertext>")
		return
	}
	mode := -1
	if os.Args[1] == "e" {
		mode = ENCRYPT
	} else if os.Args[1] == "d" {
		mode = DECRYPT
	} else {
		panic("invalid mode")
	}
	iv, err := hex.DecodeString(os.Args[2])
	if err != nil {
		panic(err)
	}
	if len(iv) != 16 {
		panic("invalid IV size")
	}
	message, err := hex.DecodeString(os.Args[3])
	if err != nil {
		panic(err)
	}
	if mode == DECRYPT && len(message)%aes.BlockSize != 0 {
		panic("ciphertext is not a multiple of the block size")
	}

	key, _ := hex.DecodeString("269306fe48bf3c6b1028ffcdfd0c6a7c")

	block, err := aes.NewCipher(key)

	data := make([]byte, len(message))

	if mode == ENCRYPT {
		encrypter := cipher.NewCBCEncrypter(block, iv)
		padlen := 16 - (len(message) % 16)
		padding := bytes.Repeat([]byte{byte(padlen)}, padlen)
		data = append(message, padding...)
		encrypter.CryptBlocks(data, data)

	} else if mode == DECRYPT {
		decrypter := cipher.NewCBCDecrypter(block, iv)
		decrypter.CryptBlocks(data, message)
		padlen := int(data[len(data)-1])
		if padlen < 1 || padlen > 16 {
			fmt.Println("INVALID PADDING")
			os.Exit(1)
		}
                for i:=0; i < padlen; i++ {
                    if int(data[len(data)-1-i]) != padlen {
			fmt.Println("INVALID PADDING")
			os.Exit(1)
                    }
                }
		data = data[:len(data)-padlen]
	}

	fmt.Printf("%s\n", hex.EncodeToString(data))
}
