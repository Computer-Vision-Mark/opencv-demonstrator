/** @file ocv-demo-item.hpp
 *  @brief Classe de base pour toutes les d�monstrations
 *
    Copyright 2015 J.A. / http://www.tsdconseil.fr

    Project web page: http://www.tsdconseil.fr/log/opencv/demo/index-en.html

    This file is part of OCVDemo.

    OCVDemo is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OCVDemo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with OCVDemo.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef OCVDEMO_ITEM_HPP
#define OCVDEMO_ITEM_HPP

#include "cutil.hpp"
#include "modele.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace utils::model;

////////////////////////////////////////////////////////////////////////////
/** @brief Classe de base pour toutes les d�monstrations OpenCV */
class OCVDemoItem
{
public:

  /** Propri�t�s d'une d�monstration OpenCV */
  struct OCVDemoItemProprietes
  {
    /** Chaine d'identification (pour retrouver le sch�ma XML) */
    std::string id;

    /** N�cessite un masque ? (exemple : inpainting) */
    bool requiert_masque;

    /** N�cessite la s�lection d'une r�gion d'int�r�t ? */
    bool requiert_roi;

    /** N�cessite la s�lection d'une suite d'image ? */
    int requiert_mosaique;

    struct MosaiqueProps
    {
      int min, max; // Nombre min / max d'images n�cessaires
      MosaiqueProps(){min = -1; max = -1;}
    } mosaique;
  };

  /** R�glages d'une d�monstration OpenCV */
  struct OCVDemoItemParams
  {
    /** Mod�le (configuration du traitement) */
    Node modele;

    /** Si oui, rectangle d�finissant la ROI */
    cv::Rect roi;

    /** Si oui, valeur du masque */
    cv::Mat masque;

    /** Si oui, liste des images d'entr�e */
    std::vector<Mat> mosaique;
  };

  /** Sortie */
  struct OCVDemoItemSortie
  {
    /** Nombre d'images produites */
    int nb_sorties;

    /** Images de sortie */
    cv::Mat O[5];

    /** Nom des diff�rentes images de sortie */
    std::string outname[5];

    /** Message d'erreur si �chec */
    std::string errmsg;

    /** TO DEPRECATE? Pointeur vers la "vraie" image de sortie ???? to remove !!!! */
    Mat vrai_sortie;
  };

  /** Propri�t�s de la d�mo */
  OCVDemoItemProprietes props;

  /** R�glages de la d�mo */
  OCVDemoItemParams params;

  /** R�sultat de l'ex�cution de la d�mo */
  OCVDemoItemSortie sortie;

  /** Calcul effectif */
  virtual int calcul(Node &model, cv::Mat &I) = 0;

  /** Constructeur */
  OCVDemoItem(){sortie.nb_sorties = -1; props.requiert_roi = false; props.requiert_masque = false; props.requiert_mosaique = false;}

  /** Destructeur */
  virtual ~OCVDemoItem(){}

  /** To deprecate? Appel� d�s lors que la ROI a chang� */
  virtual void set_roi(const cv::Mat &I, const cv::Rect &new_roi){params.roi = new_roi;}

  /** To deprecate? */
  virtual int configure_ui(){return 0;}

  /** To deprecate? */
  virtual void setup_model(Node &model) {}

protected:
  utils::Logable journal;
};





#endif /* OCVDEMO_ITEM_HPP_ */
