#! /bin/zsh

cd OCR && cmake_clean.sh && cmake_run.sh
cd ..
ln -s ./OCR/ocr_engine ocr
