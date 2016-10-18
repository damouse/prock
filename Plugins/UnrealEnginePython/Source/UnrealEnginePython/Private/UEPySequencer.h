#pragma once



#include "UnrealEnginePython.h"

PyObject *py_ue_sequencer_master_tracks(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_possessable_tracks(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_track_sections(ue_PyUObject *, PyObject *);
#if WITH_EDITOR
PyObject *py_ue_sequencer_folders(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_set_display_name(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_get_display_name(ue_PyUObject *, PyObject *);
#endif
PyObject *py_ue_sequencer_sections(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_possessables(ue_PyUObject *, PyObject *);
PyObject *py_ue_sequencer_find_possessable(ue_PyUObject *, PyObject *);

PyObject *py_ue_sequencer_add_master_track(ue_PyUObject *, PyObject *);
