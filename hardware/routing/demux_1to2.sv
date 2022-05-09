module demux_1to2 #(parameter WORD_SIZE = 16)
                 (input logic [WORD_SIZE - 1:0] data_in,
                  input logic sel,
                  output logic [WORD_SIZE - 1:0] data_out_0, data_out_1);

    always_comb begin
        case (sel)
            1'd0: data_out_0 = data_in;
            1'd1: data_out_1 = data_in;
        endcase
    end
endmodule
