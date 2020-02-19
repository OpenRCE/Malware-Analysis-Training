/*
    Function Analyzer Header
    Copyright (C) 2005 Pedram Amini <pamini@idefense.com,pedram.amini@gmail.com>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    this program; if not, write to the Free Software Foundation, Inc., 59 Temple
    Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __FUNCTION_ANALYZER_H__
#define __FUNCTION_ANALYZER_H__

#include "funcx.h"
//#include "loop_detection.h"

#define FA_DISASM_BUFLEN        512

#define FA_IGNORE_CALLS         0x1
#define FA_INSTRUCTIONS_ONLY    0x2
#define FA_TOKENIZE_JUMPS       0x4

#define FA_SIGNED_TOKEN         "signed"
#define FA_UNCONDITIONAL_TOKEN  "unconditional"
#define FA_UNSIGNED_TOKEN       "unsigned"

#undef FA_DEBUG
//#define DEBUG_FA
// IDA's wrapped malloc routines are not cooperating with me.
#define qalloc   malloc
#define qrealloc realloc
#define qfree    free



class function_analyzer 
{
	friend class loop_detection;

	public:    
		ea_t get_node(ea_t ea);
	    ea_t find_src(ea_t ea);
	    int is_reference_to(ea_t to, ea_t ref);
	    int get_num_references_to(ea_t ea);
	     function_analyzer (int);
         function_analyzer (ea_t);
		 function_analyzer (func_t * fptr);
        ~function_analyzer ();

        // public member routines.
        bool disasm       (ea_t, char *);
        ea_t first_ea     (void) { return ea_start; }
        ea_t last_ea      (void) { return ea_end;   }
        ea_t next_ea      (ea_t);
        ea_t prev_ea      (ea_t);
        void graph        (void);
        void run_analysis (void);

        // getters.
        ea_t          get_call_dst         (int i) { return calls_dst[i];     }
        ea_t          get_call_src         (int i) { return calls_src[i];     }
        unsigned long get_crc              (void)  { return crc;              }
        int           get_disasm_flags     (void)  { return disasm_flags;     }
        ea_t          get_ea_start         (void)  { return ea_start;         }
        ea_t          get_ea_end           (void)  { return ea_end;           }
        ea_t          get_edge_dst         (int i) { return edges_dst[i];     }
        ea_t          get_edge_src         (int i) { return edges_src[i];     }
        int           get_function_id      (void)  { return function_id;      }
        char *        get_md5              (void)  { return md5;              }
        ea_t          get_node             (int i) { return nodes[i];         }
        int           get_num_nodes        (void)  { return num_nodes;        }
        int           get_num_edges        (void)  { return num_edges;        }
        int           get_num_calls        (void)  { return num_calls;        }
        int           get_num_instructions (void)  { return num_instructions; }
        ea_t          get_size             (void)  { return size;             }

        // setters.
        void set_disasm_flags          (int   t) { disasm_flags          = t; }
        void set_finetuning            (bool  t) { finetuning            = t; }
        void set_layout_downfactor     (int   t) { layout_downfactor     = t; }
        void set_manhattan_edges       (bool  t) { manhattan_edges       = t; }
        void set_sort_nodes            (bool  t) { sort_nodes            = t; }
        void set_splines               (bool  t) { splines               = t; }
        void set_strip_comments        (bool  t) { strip_comments        = t; }
        void set_xlspace               (int   t) { xlspace               = t; }
        void set_xspace                (int   t) { xspace                = t; }
        void set_color                 (char *t) { strncpy(color,            t, sizeof(color));            }
        void set_color_far_off         (char *t) { strncpy(color_far_off,    t, sizeof(color_far_off));    }
        void set_color_node            (char *t) { strncpy(color_node,       t, sizeof(color_node));       }
        void set_layout_algorithm      (char *t) { strncpy(layout_algorithm, t, sizeof(layout_algorithm)); }

    private:
        // internal member routines.
        bool add_call        (ea_t);
        bool add_edge        (ea_t, ea_t);
        bool add_node        (ea_t);
        bool add_instruction (ea_t);
        void analyze         (ea_t);
        void crc_build_table (void);
        void crc_calculate   (void);
        void constructor     (func_t *);
        int  find_node_index (ea_t);
        bool is_node         (ea_t);
        void md5_digest      (void);
        void quick_sort      (ea_t, ea_t);

        // internal variables.
        // when looping on num_{nodes,edges,calls} use:
        //     for (i = 1; i <= num_{nodes,edges,calls}; i++)
        unsigned long crc;                       // calculated crc checksum.
        int           disasm_flags;              // disassembly options.
        ea_t          ea_start;                  // starting address.
        ea_t          ea_end;                    // ending address.
        int           function_id;               // internal function id.
        char          function_name[MAXNAMELEN]; // function name.
        char          md5[33];                   // calculated md5 hash (+1 for null termination).
        int           num_nodes;                 // isomorphism node count.
        int           num_edges;                 // isomorphism edge count.
        int           num_calls;                 // isomorphism call count.
        int           num_instructions;          // number of instructions in this routine.
        ea_t          size;                      // ending address - starting address.

        // internal lists.
        ea_t          *calls_src;                // list of call sources.
        ea_t          *calls_dst;                // list of call destinations.
        ea_t          *edges_src;                // list of source edges.
        ea_t          *edges_dst;                // list of destination edges.
        ea_t          *nodes;                    // list of nodes.
        ea_t          *instructions;             // list of instructions in this routine.

        // internal table used in crc calculations.
        unsigned long crc_table[256];

        // internal graph variables.
        char color[64];
        char color_far_off[64];
        char color_node[64];
        bool finetuning;
        char layout_algorithm[64];
        int  layout_downfactor;
        bool manhattan_edges;
        bool sort_nodes;
        bool splines;
        bool strip_comments;
        int  xlspace;
        int  xspace;

		
};
#endif
